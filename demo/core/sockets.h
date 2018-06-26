#ifndef __ODAS_DEMO_CORE_SOCKETS
#define __ODAS_DEMO_CORE_SOCKETS

	typedef struct sockets {

		unsigned int raw;
		unsigned int targets;

		unsigned int pots;
		unsigned int tracks;
		unsigned int seps;
		unsigned int pfs;

	} sockets;

	sockets * sockets_construct(void);

	void sockets_destroy(sockets * scks);

	void sockets_load(sockets * scks, const char * file);

	void sockets_printf(const sockets * scks);

	void sockets_validate(int token);

#endif