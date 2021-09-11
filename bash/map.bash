if [ $# -gt 0 ];
then
	dir="$(pwd)/$1"
else
	dir="$(pwd)/"
fi

allf=`ls $dir`

for fn in $allf
do
	echo $fn
done
