
#ifndef PSPPHONE_CONFIG_H
#define PSPPHONE_CONFIG_H

void config_set_server(char *server);
void config_set_user(char *user);
void config_set_password(char *password);
void config_set_nat_traversal(int natted);
void config_set_stun_server(char *server);
void config_set_stun_port(int port);
void config_set_use_video(int video);
void config_set_test_mode(int mode);
void config_set_usb(int usb);
void config_set_headset(int headset);
void config_set_inputfile(int file);
void config_set_logfile(char *file);

char *config_get_user(void);
char *config_get_user_uri(void);
char *config_get_server_uri(void);
char *config_get_password(void);
int config_get_nat_traversal(void);
char *config_get_stun_server(void);
int config_get_stun_port(void);
int config_get_use_video(void);
int config_get_test_mode(void);
int config_use_usb(void);
int config_use_headset(void);
int config_use_inputfile(void);
char *config_get_logfile(void);

#endif
