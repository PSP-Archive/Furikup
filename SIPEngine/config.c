#include <string.h>
#include <stdio.h>
 
#include "config.h"
#include "video.h"

char configServer[128] = {0};
char configUser[128] = {0};
char configPassword[64] = {0};
char configStunServer[128] = {0};
char logFile[128] = {0};
int configStunPort = 3478;
int configNat = 0;
int useVideo = 0;
int useUsb = 0;
int useHeadset = 0;
int useTestMode = 0;
int useInputFile = 0;

void config_set_server(char *server)
{
	strncpy(configServer, server, 128);
}

void config_set_user(char *user)
{
	strncpy(configUser, user, 128);
}

void config_set_password(char *password)
{
	strncpy(configPassword, password, 64);
}

void config_set_nat_traversal(int natted)
{
	configNat = natted;
}

void config_set_stun_server(char *server)
{
	strncpy(configStunServer, server, 128);
	configNat = 1;
}

void config_set_stun_port(int port)
{
	configStunPort = port;
}

void config_set_use_video(int video)
{
	useVideo = video;
}

void config_set_usb(int usb)
{
	useUsb = usb;
}

void config_set_headset(int headset)
{
	useHeadset = headset;
}

void config_set_inputfile(int file)
{
	useInputFile = file;
}

void config_set_test_mode(int mode)
{
	useTestMode = mode;
}

void config_set_logfile(char *file)
{
	strcpy(logFile, file);
}

char *config_get_user(void)
{
	return configUser;
}

char *config_get_user_uri(void)
{
	static char user_uri[512];

	sprintf(user_uri, "sip:%s@%s", configUser, configServer);

	return user_uri;
}

char *config_get_server_uri(void)
{
	static char server_uri[256];

	sprintf(server_uri, "sip:%s", configServer);

	return server_uri;
}

char *config_get_password(void)
{
	return configPassword;
}

int config_get_nat_traversal(void)
{
	return configNat;
}

char *config_get_stun_server(void)
{
	return configStunServer;
}

int config_get_stun_port(void)
{
	return configStunPort;
}

int config_get_use_video(void)
{
	return useVideo;
}

int config_use_usb(void)
{
	return useUsb;
}

int config_use_headset(void)
{
	return useHeadset;
}

int config_use_inputfile(void)
{
	return useInputFile;
}

int config_get_test_mode(void)
{
	return useTestMode;
}

char *config_get_logfile(void)
{
	return logFile;
}
