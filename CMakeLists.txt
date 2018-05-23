cmake_minimum_required(VERSION 3.9)
project(ls)

set(CMAKE_CXX_STANDARD 11)


add_executable(ls
            test.c)
link_libraries(ls "libft.a" "../done/ft_printf/libftprintf.a")
