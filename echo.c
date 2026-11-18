#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

static void write_all(int fd, const char *data, ssize_t length)
{
	ssize_t sent = 0;

	while (sent < length) {
		ssize_t result = write(fd, data + sent, length - sent);

		if (result <= 0) {
			return;
		}

		sent += result;
	}
}

int main(int argc, char *argv[])
{
	int num_files = argc - 1;
	int fds[num_files > 0 ? num_files : 1];
	char buffer[BUFFER_SIZE];
	ssize_t received;

	for (int i = 0; i < num_files; i++) {
		fds[i] = open(argv[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}

	while ((received = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0) {
		write_all(STDOUT_FILENO, buffer, received);

		for (int i = 0; i < num_files; i++) {
			write_all(fds[i], buffer, received);
		}
	}

	for (int i = 0; i < num_files; i++) {
		close(fds[i]);
	}

	return 0;
}
