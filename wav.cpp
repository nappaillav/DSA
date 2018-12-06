#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>
#include <cstring>
using namespace std;


typedef struct  WAV_HEADER
{
    /* RIFF Chunk Descriptor */
    uint8_t         RIFF[4];        // RIFF Header Magic header
    uint32_t        ChunkSize;      // RIFF Chunk Size
    uint8_t         WAVE[4];        // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t         fmt[4];         // FMT header
    uint32_t        Subchunk1Size;  // Size of the fmt chunk
    uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t        NumOfChan;      // Number of channels 1=Mono 2=Sterio
    uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
    uint32_t        bytesPerSec;    // bytes per second
    uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
    uint16_t        bitsPerSample;  // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t         Subchunk2ID[4]; // "data"  string
    uint32_t        Subchunk2Size;  // Sampled data length
} wav_hdr;

// find the file size
int getFileSize(FILE* inFile)
{
    int fileSize = 0;
    fseek(inFile, 0, SEEK_END);

    fileSize = ftell(inFile);

    fseek(inFile, 0, SEEK_SET);
    return fileSize;
}

// circular convolution 
float *circular_conv(float x[],float h[] ,int N){
	float *y=new float[N];
	float total=0.0;
	int m=0,n,k;
	for(m=0;m<N;m++){
		total=0.0;
  		for(k=0;k<N;k++){
   			if((m-k)>=0)
    			n=m-k;
   			else
    			n=m-k+N;
			total=total+x[k]*h[n];
 	 	}
  	y[m]=total;

 }
	return y;
}
// overlap and save method 
float *overlap_save(short int x[],float h[] ,int l, int n, int L){
	/*
	Variables 
	x- input signal array
	h- filter coefficients
	l- length of corresponding to the smaller array of x for overlap and save
	n- length of filter coefcients (h)
	L- length of input signal (x)
	
	
	
	*/
	int m = l+n-1;
	float arr[50000]={0};
	float X[100]={0};
	float H[100]={0};
	float *y;
	int count=0;
	float *out=new float[50000];
	int j,i,k;
	for(i=n-1;i<(L+n-1);i++){
		arr[i]=x[i-n+1];	
		}
	
	for(i=0;i<n;i++){
		H[i]=h[i];
		}
	j=0;
	while(j<(L+n-1)){
	
		for(i=j;i<(j+m);i++){
			X[i-j]=arr[i];
			}
		y=circular_conv(X,H,m);
	
		for(i=n-1;i<m;i++){
			out[count]=y[i];
			count++;
			}
	
		j=j+l;	
	}	
	return out;
	}



int main()
{   
    wav_hdr wavHeader;
    int headerSize = sizeof(wav_hdr), filelength = 0;
	short int X[50000];
    const char* filePath;
    string input;
	// filter coefficient 
	/* Specification
	FIR filter order : 17 
	Fpass  = 2000;       
	Fstop  = 10000;       
	Fs=48000;
	Rp  = 0.00005;   
	Rst = 1e-4;  Corresponds to 80 dB stopband attenuation
	*/
	float b[17]={-0.0120787,0.024248,0.025792,-0.050285,-0.046996,-0.015378,0.133978,0.267828,0.345784,0.267828,0.133977,-0.015377,-0.046996,-0.050285,0.025792,0.024248,-0.012079};

    /*cout << "Input wave file name: ";
    cin >> input;
    cin.get();
    filePath = input.c_str();
	*/

    FILE* wavFile = fopen("input_signal.wav", "r");
    if (wavFile == nullptr)
    {
        fprintf(stderr, "Unable to open wave file: %s\n", filePath);
        return 1;
    }

    //Read the header
    size_t bytesRead = fread(&wavHeader, 1, headerSize, wavFile);
    // cout << "Header Read " << bytesRead << " bytes." << endl;
    if (bytesRead > 0)
    {
        //Read the data
        uint16_t bytesPerSample = wavHeader.bitsPerSample / 8;      //Number of bytes per sample
        uint64_t numSamples = wavHeader.ChunkSize / bytesPerSample; //How many samples are in the wav file?
        //cout<<"number of samples = "<<numSamples<<endl;
        static const int BUFFER_SIZE = 48000; // it can also be total number of samples in wav file 
        short int *buffer = new short int[BUFFER_SIZE];

        int count=0;
        while ((bytesRead = fread(buffer, bytesPerSample, 48000, wavFile)) > 0)
        {	//cout << "Read " << bytesRead << " bytes." << endl; 	
        	for(uint16_t i=0;i<bytesRead;i++){
        		X[count] = buffer[i];
        		count=count+1;
        		}
        }
        delete [] buffer;
        buffer = nullptr;
        filelength = getFileSize(wavFile);
		
		float *y;
		
		/*
		Variables 
		x- input signal array
		h- filter coefficients
		l- length of corresponding to the smaller array of x for overlap and save
		n- length of filter coefcients (h)
		L- length of input signal (x)
	
		
	    in general case L = numSamples in wav file
		*/
		y = overlap_save(X,b,20,17,48000);
		// (numSamples-124+17-1) ~ l+n-1
		for(int k = 0;k<(48000+17-1);k++)
			cout<<y[k]<<endl;
		/*
        cout << "File is                    :" << filelength << " bytes." << endl;
        cout << "RIFF header                :" << wavHeader.RIFF[0] << wavHeader.RIFF[1] << wavHeader.RIFF[2] << wavHeader.RIFF[3] << endl;
        cout << "WAVE header                :" << wavHeader.WAVE[0] << wavHeader.WAVE[1] << wavHeader.WAVE[2] << wavHeader.WAVE[3] << endl;
        cout << "FMT                        :" << wavHeader.fmt[0] << wavHeader.fmt[1] << wavHeader.fmt[2] << wavHeader.fmt[3] << endl;
        cout << "Data size                  :" << wavHeader.ChunkSize << endl;
		cout << "Sample Count               :" << (wavHeader.ChunkSize*8)/(wavHeader.bitsPerSample)<<endl;
        // Display the sampling Rate from the header
        cout << "Sampling Rate              :" << wavHeader.SamplesPerSec << endl;
        cout << "Number of bits used        :" << wavHeader.bitsPerSample << endl;
        cout << "Number of channels         :" << wavHeader.NumOfChan << endl;
        cout << "Number of bytes per second :" << wavHeader.bytesPerSec << endl;
        cout << "Data length                :" << wavHeader.Subchunk2Size << endl;
        cout << "Audio Format               :" << wavHeader.AudioFormat << endl;
        // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM

        cout << "Block align                :" << wavHeader.blockAlign << endl;
        cout << "Data string                :" << wavHeader.Subchunk2ID[0] << wavHeader.Subchunk2ID[1] << wavHeader.Subchunk2ID[2] << wavHeader.Subchunk2ID[3] << endl;
*/
    }
    fclose(wavFile);
    return 0;
}


