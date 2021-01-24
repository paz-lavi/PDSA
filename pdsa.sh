usage () {
echo "\nUsage:\n   $ pdsa <command> [<args>]\n"
echo "\nsign-file ...................... sign on a file"
echo "\nvalidate-key-and-file .......... check if signature match to file"
echo "\nvalidate-signed-file ........... check if signed file is valid (not modified)"
echo "\nkeys-generator ................. generate new key pair\n"
}

run_program(){

    case $1 in

  sign-file)
    ./sign-file.o "${@:2}"
    ;;

  validate-key-and-file)
    ./validate-key-and-file.o "${@:2}"
    ;;

  validate-signed-file)
    ./validate-signed-file.o "${@:2}"
    ;;

  
  keys-generator)
    ./keys-generator.o "${@:2}"
    ;;

  help )
    usage
    ;;

  *)
    echo  "command not found"
    ;;
esac

}

if [ $# -eq 0 ]
    then
        usage
    else
        run_program $@
fi
