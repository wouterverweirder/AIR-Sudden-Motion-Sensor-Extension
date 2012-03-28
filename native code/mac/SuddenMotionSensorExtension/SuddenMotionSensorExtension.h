#include <Adobe AIR/Adobe AIR.h>

extern "C"
{
    void contextInitializer(void* extData, const uint8_t* ctxType, FREContext ctx, uint32_t* numFunctions, const FRENamedFunction** functions);
    void contextFinalizer(FREContext ctx);
    
    void initializer(void** extData, FREContextInitializer* ctxInitializer, FREContextFinalizer* ctxFinalizer);
	void finalizer(void* extData);
    
    FREObject SMS_isSupported(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[]);
    FREObject SMS_startListening(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[]);
    FREObject SMS_stopListening(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[]);
    FREObject SMS_setRequestedUpdateInterval(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[]);
    FREObject SMS_setMode(FREContext ctx, void* funcData, uint32_t argc, FREObject argv[]);
}