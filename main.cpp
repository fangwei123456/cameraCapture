#include "gstCamera.h"
#include "cudaNormalize.h"
#include "gstUtility.h"

int main(int argc, char *argv[])
{

	gst_init(&argc, &argv);

	gstCamera* camera = gstCamera::Create(1280,720,-1);

	const size_t texSz = camera->GetWidth() * camera->GetHeight() * 3 / 2;

	if( !camera )
	{
		printf("\ngst-camera:  failed to initialize video device\n");
		return 0;
	}

	printf("\ngst-camera:  successfully initialized video device\n");
	printf("    width:  %u\n", camera->GetWidth());
	printf("   height:  %u\n", camera->GetHeight());
	printf("    depth:  %u (bpp)\n", camera->GetPixelDepth());

	if( !camera->Open() )
	{
		printf("\ngst-camera:  failed to open camera for streaming\n");
		return 0;
	}

	printf("\ngst-camera:  camera open for streaming\n");


		while( 1 )
		{


			void* imgCPU  = NULL;
			void* imgCUDA = NULL;

			// get the latest frame

			if( !camera->Capture(&imgCPU, &imgCUDA, 40000) )
				printf("\ngst-camera:  failed to capture frame\n");
			else
			{
				printf("gst-camera:  recieved new frame  CPU=0x%p  GPU=0x%p\n", imgCPU, imgCUDA);
				void* imgRGBA = NULL;

				if( !camera->ConvertRGBA(imgCUDA, &imgRGBA, true) )
						printf("gst-camera:  failed to convert from NV12 to RGBA\n");

				//const float4 px = ((float4*)imgRGBA)[y * camera->GetWidth() + x];


			}




		}
		printf("\ngst-camera:  un-initializing video device\n");

		camera->Close();
		delete camera;


	return 0;
}
