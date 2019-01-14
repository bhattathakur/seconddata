#trying to copy the given file into number of consecutive files:
read -p "File number to be copied ?: " FILENUMBER
read -p "Final file  to be copied ?: " TOTALFILES
DAT=".dat"
TABULATED="tabulatedenergy"
echo "Input File  :$TABULATED$FILENUMBER$DAT"
#NEXT=$((FILENUMBER+1)) 

#For loop to copy files:
while [ $FILENUMBER -lt $TOTALFILES ]
do
    NEXT=$((FILENUMBER+1))
    THIS="$TABULATED$FILENUMBER$DAT"
    OTHER="$TABULATED$NEXT$DAT"
    # cp "$TABULATED$FILENUMBER$DAT" "$TABULATED$NEXT$DAT"
    cp $THIS $OTHER
    
    echo "Tabulated Original File : $TABULATED$FILENUMBER$DAT"
    echo "Copied to this     File : $TABULATED$NEXT$DAT"
    ((FILENUMBER++))
done
