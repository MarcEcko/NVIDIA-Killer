#include <stdio.h>
#include <nvapi.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

int main ()
{
	NvAPI_Status Ret = NVAPI_ERROR; 
	NvPhysicalGpuHandle nvGPUHandle[NVAPI_MAX_PHYSICAL_GPUS];
	NvAPI_ShortString GpuFullName;
	NvU32 GpuCount;
	NvU32 GpuTach;
	NvPhysicalGpuHandle GPU1;

	NV_GPU_THERMAL_SETTINGS ThermalSettings;
	ThermalSettings.version = NV_GPU_THERMAL_SETTINGS_VER_2;
	ThermalSettings.sensor[0].target = NVAPI_THERMAL_TARGET_GPU;
	ThermalSettings.sensor[0].controller = NVAPI_THERMAL_CONTROLLER_GPU_INTERNAL;

	Ret = NvAPI_Initialize();

	if(Ret == NVAPI_OK)
	{
		Ret = NvAPI_EnumPhysicalGPUs(nvGPUHandle, &GpuCount);
		GPU1 = nvGPUHandle[0];

		if(Ret == NVAPI_OK)
		{
			printf("\nGPU Handle: 0x%x, GPU Count: %d", GPU1, GpuCount);

			Ret = NvAPI_GPU_GetFullName(GPU1, GpuFullName);

			if(Ret == NVAPI_OK)
			{
				printf("\nGPU Full Name: %s", GpuFullName);
				Ret = NvAPI_EnumPhysicalGPUs(nvGPUHandle, &GpuCount);
				GPU1 = nvGPUHandle[0];

				while(1)
				{
					Ret = NvAPI_GPU_GetThermalSettings(GPU1, NVAPI_THERMAL_TARGET_ALL, &ThermalSettings);
					printf("\nGPU Temperature: %d", ThermalSettings.sensor[0].currentTemp);
					Ret = NvAPI_GPU_GetTachReading(GPU1, &GpuTach);
					printf("\nGPU Fan RPM: %d", GpuTach);
					Sleep(600);
				}
			}
		}
		else
		{
			printf("Error initialize: 0x%x", Ret);
		}
		getchar();

	}
}
	