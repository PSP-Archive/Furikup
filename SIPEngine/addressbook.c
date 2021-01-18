
#include <stdio.h>
#include <string.h>

#include "sipengine.h"
#include "addressbook.h"

Contact contacts[20];
int maxContact = 0;

void strip(char *buf)
{
	char *c;

	// Strip off the \r\n
	c = strchr(buf, '\r');
	if(c)
	{
		*c = 0;
	}

	c = strchr(buf, '\n');
	if(c)
	{
		*c = 0;
	}
}

int parseAddressbook(const char *filename)
{
	Contact *con;
	char *value;
	char buffer[512];

	memset(contacts, 0, sizeof(contacts));

	FILE *fd = fopen(filename, "rb");
	if(!fd)
	{
		// File not found
		return -1;
	}

	// Now to process each line of the file
	while(fgets(buffer, 512, fd))
	{
		con = &contacts[maxContact++];

		value = strtok(buffer, ",");
		if(!value)
		{
			maxContact--;
			continue;
		}
		strip(value);
		
		strcpy(con->nickname, value);

		value = strtok(NULL, ",");
		if(!value)
		{
			maxContact--;
			continue;
		}
		strip(value);
		strcpy(con->sipuri, value);

		// Optional to supply first and last name
		value = strtok(NULL, ",");
		if(!value)
		{
			continue;
		}
		strip(value);
		strcpy(con->firstname, value);

		value = strtok(NULL, ",");
		if(!value)
		{
			continue;
		}
		strip(value);
		strcpy(con->lastname, value);
	}

	return gEventFunction(SUI_IN_ADDRESS_BOOK, contacts, maxContact);
}
