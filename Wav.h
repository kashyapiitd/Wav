#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;

class Wav_Header
{
public:
    /* Will have the Wav File Header and data*/
    char chunk_id[5];
    unsigned int chunk_size;
    char format[5];
    char sub_chunk1_id[4];
    unsigned int sub_chunk1_size;
    short audio_format;
    short number_channels;
    unsigned int sampling_rate;
    unsigned int byte_rate;
    short block_align;
    short bits_per_sample;
    char sub_chunk2_id[5];
    unsigned int sub_chunk2_size;
};
enum class status {
    FILE_NOT_OPENED,
    INCORRECT_CHUNK_ID,
    INCORRECT_FORMAT,
    INCORRECT_SUB_CHUNK1_ID,
    INCORRECT_SUB_CHUNK1_SIZE,
    INCORRECT_AUDIO_FORMAT,
    INCORRECT_NUM_CHANNELS,
    INCORRECT_BYTE_RATE,
    INCORRECT_BLOCK_ALIGN,
    INCORRECT_SUB_CHUNK2_ID,
    INCORRECT_SUB_CHUNK2_SIZE,
    INCORRECT_DATA_SIZE,
    SUCESS
};
class Wav
{
public:
    struct Wav_Header wav_header;
    short bytes_per_sample;
    int number_samples;
    void* data;
    Wav();
    status read_wave_file(string filename);
    ~Wav();
};
