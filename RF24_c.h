#ifndef _RF24_c_H
#define _RF24_c_H

#define RF24_SIZE 18

#ifdef __cplusplus
#define CCALL extern "C"

#ifdef AVR_GENERIC
inline void * operator new(size_t size, void* ptr)
{
  return ptr;
}

void * operator new(size_t size) 
{
  return malloc(size);
}

void operator delete(void* ptr) 
{
  free(ptr);
}
#endif

CCALL RF24* rf24_init(uint8_t ce_pin, uint8_t cs_pin) { return new RF24(ce_pin, cs_pin); }
CCALL void rf24_init_stack(void* rf24, uint8_t ce_pin, uint8_t cs_pin) { new(rf24) RF24(ce_pin, cs_pin); }
CCALL void rf24_begin(RF24* rf24) { rf24->begin(); }
CCALL void rf24_startListening(RF24* rf24) { rf24->startListening(); }
CCALL void rf24_stopListening(RF24* rf24) { rf24->stopListening(); }
CCALL bool rf24_available(RF24* rf24) { return rf24->available(); }
CCALL void rf24_read(RF24* rf24, void* buf, uint8_t len) { rf24->read(buf, len); }
CCALL bool rf24_write(RF24* rf24, const void* buf, uint8_t len) { return rf24->write(buf, len); }
CCALL void rf24_openReadingPipe(RF24* rf24, uint8_t number, const uint8_t *address) { rf24->openReadingPipe(number, address); }
CCALL void rf24_openWritingPipe(RF24* rf24, const uint8_t *address) { rf24->openWritingPipe(address); }
CCALL void rf24_setChannel(RF24* rf24, uint8_t channel) { rf24->setChannel(channel); }
CCALL uint8_t rf24_getChannel(RF24* rf24) { return rf24->getChannel(); }
CCALL void rf24_setRetries(RF24* rf24, uint8_t delay, uint8_t count) { rf24->setRetries(delay, count); }
CCALL bool rf24_setDataRate(RF24* rf24, rf24_datarate_e speed) { return rf24->setDataRate(speed); }
CCALL void rf24_free(RF24* rf24) { delete rf24; }
void rf24_free_stack(RF24* rf24) { rf24->~RF24(); }

typedef struct { uint8_t data[RF24_SIZE]; } __RF24_1;
// these assert that we've got the structure size and alignment right for the C interface below
static_assert(sizeof(RF24) == RF24_SIZE, "WRONG constant size for RF24 C interface. Recalculate and update the #define");
static_assert(sizeof(RF24) == sizeof(__RF24_1), "WRONG size of predefined struct");

#else 

typedef struct { uint8_t data[RF24_SIZE]; } RF24;

typedef enum { RF24_1MBPS = 0, RF24_2MBPS, RF24_250KBPS } rf24_datarate_e;

RF24* rf24_init(uint8_t ce_pin, uint8_t cs_pin);
void rf24_init_stack(RF24* rf24, uint8_t ce_pin, uint8_t cs_pin);
void rf24_begin(RF24* rf24);
void rf24_startListening(RF24* rf24);
void rf24_stopListening(RF24* rf24);
bool rf24_available(RF24* rf24);
void rf24_read(RF24* rf24, void* buf, uint8_t len);
bool rf24_write(RF24* rf24, const void* buf, uint8_t len);
void rf24_openReadingPipe(RF24* rf24, uint8_t number, const uint8_t *address);
void rf24_openWritingPipe(RF24* rf24, const uint8_t *address);
void rf24_setChannel(RF24* rf24, uint8_t channel);
uint8_t rf24_getChannel(RF24* rf24);
void rf24_setRetries(RF24* rf24, uint8_t delay, uint8_t count);
bool rf24_setDataRate(RF24* rf24, rf24_datarate_e speed);
void rf24_free(RF24* rf24);
void rf24_free_stack(RF24* rf24);
#endif

#endif
