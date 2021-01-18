#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "config_file.h"
#include "config.h"
#include "sipengineif.h"

char buffer[512];

void handleOption(char *option, char *value)
{
	if(strcasecmp(option, "server") == 0)
	{
		config_set_server(value);
	}
	else if(strcasecmp(option, "username") == 0)
	{
		if (strcmp(value, "1234567") == 0)
		{
			ErrorMessage("you haven't set up your sipcfg.ini - see the readme.txt");
		}
		config_set_user(value);
	}
	else if(strcasecmp(option, "password") == 0)
	{
		config_set_password(value);
	}
	else if(strcasecmp(option, "disablenat") == 0)
	{
		// Only used as a hack for testing
		if(strcasecmp(value, "yes") == 0)
		{
			config_set_nat_traversal(0);
		}
	}
	else if(strcasecmp(option, "stunserver") == 0)
	{
		config_set_stun_server(value);
	}
	else if(strcasecmp(option, "stunport") == 0)
	{
		config_set_stun_port(atoi(value));
	}
	else if(strcasecmp(option, "input") == 0)
	{
		if(strcasecmp(value, "usbcam") == 0)
		{
			config_set_usb(1);
			config_set_use_video(1);
		}
		else if(strcasecmp(value, "usbmic") == 0)
		{
			config_set_usb(1);
		}
		else if(strcasecmp(value, "headset") == 0)
		{
			// Defaults to use the HPRM
			config_set_headset(1);
		}
		else if(strcasecmp(value, "file") == 0)
		{
			config_set_inputfile(1);
		}
	}
	else if(strcasecmp(option, "logfile") == 0)
	{
		config_set_logfile(value);
	}
	else if(strcasecmp(option, "test") == 0)
	{
		// Only to allow for errors to be ignored (eg no camera)
		config_set_test_mode(1);
	}
}

int parseConfigFile(const char *filename)
{
	FILE *fd = fopen(filename, "rb");
	char *option;
	char *value;
	char *c;
	int i;

	if(!fd)
	{
		// File not found
		return -1;
	}

	// Now to process each line of the file
	while(fgets(buffer, 512, fd))
	{
		if (buffer[0] == '#')
		{
			continue;
		}

		option = strtok(buffer, "=");
		if (!option)
		{
			fclose(fd);
			return -2;
		}

		value = strtok(NULL, "=");
		if (!value)
		{
			fclose(fd);
			return -3;
		}

		// Strip off the \r\n
		c = strchr(value, '\r');
		if(c)
		{
			*c = 0;
		}

		c = strchr(value, '\n');
		if(c)
		{
			*c = 0;
		}

		// Strip off any trailing spaces
		for(i=strlen(value)-1; i!=0; i--)
		{
			if(value[i] == ' ')
			{
				value[i] = 0;
			}
			else
			{
				break;
			}
		}
		
		handleOption(option, value);
	}

	fclose(fd);

	return 0;
}
