#include "pafe.h"

class FelicaReader : public Nan::AsyncWorker {
public:
  FelicaReader(Nan::Callback *callback)
    : AsyncWorker(callback) {}
  ~FelicaReader() {}

  void Execute() {
    pasori *reader = pasori_open();
    felica *f;
    int ret;
    uint8_t raw_idm[16];
    if (reader == NULL) {
      SetErrorMessage("failed to open reader");
      return;
    }
    ret = pasori_init(reader);
    if (ret != 0) {
      pasori_close(reader);
      SetErrorMessage("failed to init reader");
      return;
    }
    f = felica_polling(reader, FELICA_POLLING_ANY, 0, 0);
    ret = felica_get_idm(f, raw_idm);
    if (ret != 0) {
      free(f);
      pasori_close(reader);
      SetErrorMessage("failed to read IDm");
      return;
    }
    sprintf(idm, "%02x%02x%02x%02x%02x%02x%02x%02x",
            raw_idm[0], raw_idm[1], raw_idm[2], raw_idm[3],
            raw_idm[4], raw_idm[5], raw_idm[6], raw_idm[7]);
    free(f);
    pasori_close(reader);
  }

  void HandleOKCallback () {
    Nan::HandleScope scope;

    v8::Local<v8::Value> argv[] = {
      Nan::Null(),
      Nan::New(idm).ToLocalChecked()
    };
    
    callback->Call(2, argv);
  }
private:
  char idm[17];
};

NAN_METHOD(readIDm) {
  Nan::Callback *callback = new Nan::Callback(info[0].As<v8::Function>());

  AsyncQueueWorker(new FelicaReader(callback));
}

NAN_MODULE_INIT(Init) {
  NAN_EXPORT(target, readIDm);        
}

NODE_MODULE(pafe, Init)
