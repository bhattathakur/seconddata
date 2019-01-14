#Simple For loop
# NAMES="Brad Kevin Alice Mark"
# for NAME in $NAMES
#     do
# 	echo "Hello $NAME"
# done
#For loop to rename the files
# FILES=$(ls *.txt)
# NEW="new"
# for FILE in $FILES
# do
#     echo "Copying $FILE to new-$FILE"
#     cp $FILE $NEW-$FILE
# done
#While loop to read line by line of a file
# LINE=1
# while read -r CURRENT_LINE
# do
#     echo "$LINE:$CURRENT_LINE"
#     ((LINE++))
# done < "testemacs.txt"
# function sayHello()
# {
#     echo "Hello World"
#     }
# sayHello

#Functions with parameters
# function greet()
# {
#     echo "Hello, I am $1 and I am $2"
    
#     }
# greet "Thakur" "30"

#Need to read the file

#Need to define the function
#Prompting the User:
read -p "Enter the file number: " FILENUMBER
echo "You entered the file $FILENUMBER"
FILEPREVIOUS=$((FILENUMBER - 1));
echo "File before this is $FILEPREVIOUS"
#Rootfiles
DAT=".dat"
TABlE="tabulated"
INITIAL="initialestimates"
FINAL="finalestimates"
TABULATEDPAST="$TABlE$FILEPREVIOUS$DAT"
TABULATED="$TABlE$FILENUMBER$DAT"
INITILAESTIMATES="$INITIAL$FILENUMBER$DAT"
FINALESTIMATES="$FINAL$FILEPREVIOUS$DAT"
FINALESTIMATES_THIS=$FINAL$FILENUMBER$DAT

echo "Tabulated-Energy-previous-file : "$TABULATEDPAST
echo "Tabulated-Energy-this-file     : "$TABULATED
echo "Final-Estimates-previous-file  : "$FINALESTIMATES
echo "Initial-Estimates-this-file    : "$INITILAESTIMATES
echo "Final-Estimates-this-file      : "$FINALESTIMATES_THIS
cp $TABULATEDPAST $TABULATED
cp $FINALESTIMATES $INITILAESTIMATES
cp $INITILAESTIMATES $FINALESTIMATES_THIS
