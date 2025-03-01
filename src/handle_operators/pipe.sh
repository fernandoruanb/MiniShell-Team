#!/usr/bin/env bash

cc handle_pipe_op.c ft_write_mode.c ft_read_mode.c ft_write_read_mode.c utils/close_descriptors.c utils/fulfil_data_fd.c translate.c ../../libft/libft.a
