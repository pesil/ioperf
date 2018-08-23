# ioperf
Fast multi-thread single file handler. Dispatch chunks of the file to worker threads. Based on lock-free Single Producer/Single Consumer ring buffers.

All configuration options are determined with descriptions in /headers/ioperf.h.
Writer thread read the data from file /headers/ioperf.h -> input_data_filename.
Words in file should be splitted by '\n' character.

Data is read by writer thread with variable chunk size into appropriate ring buffer. Count of ring buffers is equal to count of reader threads.

Reader threads checks if their buffers is empty in cycle and, if not, reads the chunks from buffers.

First time execution would be very slow, because file will be read from disk.

At the second execution file will be read from memory if OS disk caching is enabled (by default is enabled).

Average time of 2300Mb file handling on Core i7 2.20GHz CPU with 4 physical cores and 3 reader threads is 9.3 seconds.
