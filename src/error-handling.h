int catch_signal(int signal, void (*handler)(int));

void log_error(const char *message);

void error(const char *message, void (*handler)());
