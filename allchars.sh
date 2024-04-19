for ((i=0; i<=255; i++)); do
    char=$(printf "\x$(printf %x $i)")
    output="This is $USER$char, with character $char"
	echo "$output"
done
