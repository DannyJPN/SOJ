
for var in $(find ~/SOJ -type f -executable);
do
copy=${var};

len=${#copy};
rev="";
for((i=$len-1;i>=0;i--)); do rev="$rev${copy:$i:1}"; done
$var "AssemLang$rev";

done


