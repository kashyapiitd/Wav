#include "Wav.h"
#define PRINT_SAMPLES

int main()
{
    Wav wav;
    status result = wav.read_wave_file("input_signal.wav");
    if (result != status::SUCESS)
    {
        cout << "Error while opening file!"<<endl;
        cout << static_cast<int>(result) << endl;
    }
    if (wav.bytes_per_sample == 2)
    {
#ifdef PRINT_SAMPLES
       for (int i = 0 ; i < wav.number_samples; i++)
       {
           cout << *(static_cast<short*>(wav.data) + i) << " ";
       }
       cout << endl;
#endif
    }
    else if (wav.bytes_per_sample == 4)
    {
#ifdef PRINT_SAMPLES
        for (int i = 0 ; i < wav.number_samples; i++)
        {
            cout << *(static_cast<int*>(wav.data) +i) << " ";
        }
        cout << endl;
#endif

    }
}

