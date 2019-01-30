# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    compilo_test.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfernand <tfernand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/04 13:31:27 by tfernand          #+#    #+#              #
#    Updated: 2018/11/20 19:16:07 by tfernand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/zsh
pth="files_to_compile/"
file=""

for entry in $pth/*
do
	dif=""
	if [ "${entry##*.}" = "s" ]; then
		file=`basename $entry .s`
		./asm_zaz $pth$file".s"
		mv $pth$file".cor" $pth$file".cor.zaz"
		../asm $pth$file".s"
		diff $pth$file".cor.zaz" $pth$file".cor" > /dev/null
		if [ $? -ne 0 ]; then
			echo "\033[0;31mError with "$pth$file".s";
			hexdump $pth$file".cor.zaz" > ori.tst
			hexdump $pth$file".cor" > our.tst
		else
			echo "\033[0;32m"$pth$file".s is Ok"
		fi	
		echo "\033[m"
	fi
done
