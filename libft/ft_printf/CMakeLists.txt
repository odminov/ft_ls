cmake_minimum_required(VERSION 3.9)
project(ft_printf)

set(CMAKE_CXX_STANDARD 11)

add_executable(ft_printf
        del_minus.c
        ft_atoi.c
        ft_isdigit.c
        ft_itoa_base.c
        ft_itoa_long.c
        ft_memset.c
        ft_printf.c
        ft_strchr.c
        ft_strclr.c
        ft_strcmp.c
        ft_strcpy.c
        ft_strjoin.c
        ft_strlen.c
        ft_strncpy.c
        ft_strnew.c
        ft_strrev.c
        header.h
        main.c
        my_ret.c
        parse_format.c
        parse_percent.c
        proc_base.c
        proc_int.c
        proc_ptr.c
        process_int_precision.c
        processing_char.c
        processing_string.c
        valid.c)
