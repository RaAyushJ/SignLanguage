// #include "Arduino.h"
#include <TensorFlowLite_ESP32.h>

//#include "tensorflow/lite/c/common.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"

#include "p_det_model.h"
#include "model_settings.h"

//#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"

#include <esp_heap_caps.h>

#include "esp_camera.h"

#include "img_converters.h"
//#include "Free_Fonts.h"


#include "soc/soc.h" // Disable brownout problems
#include "soc/rtc_cntl_reg.h" // Disable brownout problems



// Select camera model
// #define CAMERA_MODEL_WROVER_KIT // Has PSRAM
//#define CAMERA_MODEL_ESP_EYE // Has PSRAM
//#define CAMERA_MODEL_M5STACK_PSRAM // Has PSRAM
//#define CAMERA_MODEL_M5STACK_WIDE  // Has PSRAM
#define CAMERA_MODEL_AI_THINKER // Has PSRAM
//#define CAMERA_MODEL_TTGO_T_JOURNAL // No PSRAM

#include "camera_pins.h"
#include "downsample.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <BluetoothSerial.h>
BluetoothSerial SerialBT;
const char* ssid = "Galaxy A237573";
const char* password = "jmou2137";
const char* Gemini_Token = "AIzaSyDKVHtU_aHcxIXNhpQwT8ZcAaOgLhgG91I";
const char* Gemini_Max_Tokens = "50";


// #include <fb_gfx.h>
const char* kCategoryLabels[kCategoryCount] = {
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "K", "L", "M",
                        "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y"
};




#define TEXT "starting app..."

camera_fb_t * fb = NULL;
uint16_t *buffer;

size_t _jpg_buf_len = 0;
uint8_t * _jpg_buf = NULL;


//tflite stuff
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;

// In order to use optimized tensorflow lite kernels, a signed int8_t quantized
// model is preferred over the legacy unsigned model format. This means that
// throughout this project, input images must be converted from unisgned to
// signed format. The easiest and quickest way to convert from unsigned to
// signed 8-bit integers is to subtract 128 from the unsigned value to get a
// signed value.

#ifdef CONFIG_IDF_TARGET_ESP32S3
constexpr int scratchBufSize = 39 * 1024;
#else
constexpr int scratchBufSize = 0;
#endif
// An area of memory to use for input, output, and intermediate arrays.
constexpr int kTensorArenaSize = 81 * 1024 + scratchBufSize; //81 * 1024 + scratchBufSize;
static uint8_t *tensor_arena;//[kTensorArenaSize]; // Maybe we should move this to external

unsigned tm_to_disp;
void init_camera(){
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_RGB565;//PIXFORMAT_GRAYSCALE;//PIXFORMAT_JPEG;//PIXFORMAT_RGB565;// 
  config.fb_location = CAMERA_FB_IN_PSRAM;
  config.frame_size = FRAMESIZE_96X96;//FRAMESIZE_QVGA;//FRAMESIZE_96X96;//
  
  // if PSRAM IC present, init with UXGA resolution and higher JPEG quality
  //                      for larger pre-allocated frame buffer.
  if(psramFound()){
    // config.frame_size = FRAMESIZE_QVGA;//FRAMESIZE_96X96;//
    config.jpeg_quality = 12;
    config.fb_count = 2;
  } else {
    // config.frame_size = FRAMESIZE_QVGA;//FRAMESIZE_96X96;//
    config.jpeg_quality = 12;
    config.fb_count = 2;
  }

#if defined(CAMERA_MODEL_ESP_EYE)
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
#endif

  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    delay(1000);
    ESP.restart();
  }
#if defined(CAMERA_MODEL_M5STACK_WIDE)
  s->set_vflip(s, 1);
  s->set_hmirror(s, 1);
#endif
}
const int SENSOR_PIN = 13; // the Arduino's input pin that connects to the sensor's SIGNAL pin 

// Variables will change:
int lastState = LOW;      // the previous state from the input pin
int currentState;  

void setup() {
  
  // put your setup code here, to run once:
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);//disable brownout detector

  init_camera();
  // buffer = (uint16_t *) malloc(240*320*2);

  

  // Set text colour to orange with black background
  
  
  dstImage = (uint16_t *) malloc(DST_WIDTH * DST_HEIGHT*2);
  img192x192 = (uint16_t *) malloc(192*192*2);
  delay(200);
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  model = tflite::GetModel(ASL_1_lite_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }
  if (tensor_arena == NULL) {
    tensor_arena =  (uint8_t *) heap_caps_malloc(kTensorArenaSize, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
  }
  if (tensor_arena == NULL) {
    printf("Couldn't allocate memory of %d bytes\n", kTensorArenaSize);
    return;
  }

  // Pull in only the operation implementations we need.
  // This relies on a complete list of all the ops needed by this graph.
  // An easier approach is to just use the AllOpsResolver, but this will
  // incur some penalty in code space for op implementations that are not
  // needed by this graph.
  //
  
  // tflite::AllOpsResolver resolver;
  /*
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
      //
      */
  // NOLINTNEXTLINE(runtime-global-variables)
  //
  
  static tflite::MicroMutableOpResolver<9> micro_op_resolver;
  micro_op_resolver.AddAveragePool2D();
  micro_op_resolver.AddMaxPool2D();
  micro_op_resolver.AddReshape();
  micro_op_resolver.AddFullyConnected();
  micro_op_resolver.AddConv2D();
  micro_op_resolver.AddDepthwiseConv2D();
  // micro_op_resolver.AddReshape();
  micro_op_resolver.AddSoftmax();
  micro_op_resolver.AddQuantize();
  micro_op_resolver.AddDequantize();
  
  
  

  // Build an interpreter to run the model with.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroInterpreter static_interpreter(
      model, micro_op_resolver, tensor_arena, kTensorArenaSize, error_reporter);
  
      ////
  
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

  // Get information about the memory area to use for the model's input.
  input = interpreter->input(0);
 Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  while (!Serial)
    ;


  // wait for WiFi connection
  WiFi.begin("Galaxy A237573","jmou2137");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 SerialBT.begin("ESP32");
    Serial.begin(115200);
    pinMode(4, INPUT_PULLUP); 
}
String res="";
 
void loop() {
  // put your main code here, to run repeatedly:
  HTTPClient https;
  https.setReuse(false);
  currentState = digitalRead(4);
  Serial.print(res);
  { 
  if(currentState == HIGH){
    if (https.begin("https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash-latest:generateContent?key=" + (String)Gemini_Token)) {  // HTTPS
 
    https.addHeader("Content-Type", "application/json");
    String payload = String("{\"contents\": [{\"parts\":[{\"text\":" + res + "}]}],\"generationConfig\": {\"maxOutputTokens\": " + (String)Gemini_Max_Tokens + "}}");

    //Serial.print("[HTTPS] GET...\n");

    // start connection and send HTTP header
    int httpCode = https.POST(payload);

    // httpCode will be negative on error
    // file found at server
    Serial.print(httpCode);
    if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
      String payload = https.getString();
      //Serial.println(payload);

      DynamicJsonDocument doc(1024);


      deserializeJson(doc, payload);
      String Answer = doc["candidates"][0]["content"]["parts"][0]["text"];
      Serial.println(Answer);
         Answer.trim();
      String filteredAnswer = "";
      for (size_t i = 0; i < Answer.length(); i++) {
        char c = Answer[i];
        if (isalnum(c) || isspace(c)) {
          filteredAnswer += c;
        } else {
          filteredAnswer += ' ';
        }
      }
      Answer = filteredAnswer;
      delay(2000);
      //SerialBT.print(Answer);
    } else {
      
      SerialBT.print("Error");
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
  }
 }
  // save the the last state
  
  //Serial.println(lastState);
  delay(1000);
  for (int i = 0; i<1; i++){
  fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
    }
    if(fb){
      esp_camera_fb_return(fb);
      fb=NULL;
    }
  delay(1);
  }
  tm_to_disp=millis();
  while(millis()-tm_to_disp<5000){ //display image for 3s to get hand in right position
  // digitalWrite(4, HIGH);

  Serial.println("Position hand correctly");
  fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
    }
  uint16_t * tmp = (uint16_t *) fb->buf;

    downsampleImage((uint16_t *) fb->buf, fb->width, fb->height);
    bool jpeg_converted = frame2jpg(fb, 90, &_jpg_buf, &_jpg_buf_len);

    for (int y = 0; y < DST_HEIGHT; y++) {
      for (int x = 0; x < DST_WIDTH; x++) {
        tmp[y*(fb->width) + x] = (uint16_t) dstImage[y*DST_WIDTH +x];

      }
    }
    
    // TJpgDec.drawJpg(0,0,(const uint8_t*) _jpg_buf, _jpg_buf_len);
    upsample((uint16_t *) fb->buf);
    
    delay(15);
  
    // Serial.println((String(fb->len)).c_str());
    // Serial.println((String(sizeof(fb->buf))).c_str());
    // delay(20);

     
    if(fb){
      esp_camera_fb_return(fb);
      if(_jpg_buf){
      free(_jpg_buf);}
      fb = NULL;
      _jpg_buf = NULL;
    }
    delay(15);
  }
  
    int8_t * image_data = input->data.int8;
    // float * image_data = input->data.f;
    // Serial.println(input->dims->size);

    for (int i = 0; i < kNumRows; i++) {
      for (int j = 0; j < kNumCols; j++) {
        uint16_t pixel = ((uint16_t *) (dstImage))[i * kNumCols + j];

        // for inference
        uint8_t hb = pixel & 0xFF;
        uint8_t lb = pixel >> 8;
        uint8_t r = (lb & 0x1F) << 3;
        uint8_t g = ((hb & 0x07) << 5) | ((lb & 0xE0) >> 3);
        uint8_t b = (hb & 0xF8);

        /**
        * Gamma corected rgb to greyscale formula: Y = 0.299R + 0.587G + 0.114B
        * for effiency we use some tricks on this + quantize to [-128, 127]
        */
        int8_t grey_pixel = ((305 * r + 600 * g + 119 * b) >> 10) - 128;

        // int8_t grey_pixel = (int8_t) ((int) tst_img1[i * kNumCols + j]-128);

        image_data[i * kNumCols + j] = grey_pixel;

        // float grey_pixel = (float) ((305 * r + 600 * g + 119 * b) >> 10);// - 128;
        // grey_pixel=grey_pixel/255.0;

        // image_data[i * kNumCols + j] = grey_pixel;

        // to display
        // display_buf[2 * i * kNumCols * 2 + 2 * j] = pixel;
        // display_buf[2 * i * kNumCols * 2 + 2 * j + 1] = pixel;
        // display_buf[(2 * i + 1) * kNumCols * 2 + 2 * j] = pixel;
        // display_buf[(2 * i + 1) * kNumCols * 2 + 2 * j + 1] = pixel;
      }
    }

    

  if (kTfLiteOk != interpreter->Invoke()) {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed.");
  }
  

  TfLiteTensor* output = interpreter->output(0);
  

  // Process the inference results.
  // int8_t max_confidence = -127;
  int idx = 0;
  int idx2 =0;
  int8_t max_confidence = output->data.uint8[idx];
  int8_t max_confidence2 = output->data.uint8[idx];
  int8_t cur_confidence;
  float max_tmp = -10000.0;
 for(int i = 0; i < kCategoryCount; i++){
    float tmp=output->data.f[i];
    // Serial.println(String(tmp));

    
    cur_confidence = output->data.uint8[i];
    
    if(max_confidence < cur_confidence){
      idx2=idx;
      idx = i;
      max_confidence = cur_confidence;
    }
    if (tmp > max_tmp){
      // idx = i;
      max_tmp = tmp;
    }
  }
  Serial.println(idx);
  Serial.println(max_confidence);
  
  
  String detected= String(kCategoryLabels[idx]);
  String detected2 = String(kCategoryLabels[idx2]);
  Serial.println(detected);
  Serial.println(detected2);
  res=res+detected;

     esp_camera_fb_return(fb);
    fb = NULL;
     free(buffer);
  delay(2000);
  }
  }
