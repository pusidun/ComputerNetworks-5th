#define log_err(M,...) printf("%s %d [ERR] "M"\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define log_info(M,...) printf("%s %d [INFO] "M"\n", __FILE__, __LINE__, ##__VA_ARGS__)