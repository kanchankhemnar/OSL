#!/bin/bash

# Address book filename
ADDRESS_BOOK="addressbook.txt"

# Function to create address book if it doesn't exist
create_addressbook() {
    if [[ ! -e $ADDRESS_BOOK ]]; then
        touch "$ADDRESS_BOOK"
        echo "Address book created."
    else
        echo "Address book already exists."
    fi
}

# Function to view the address book
view_addressbook() {
    if [[ -s $ADDRESS_BOOK ]]; then
        echo "---- Address Book ----"
        cat "$ADDRESS_BOOK"
    else
        echo "Address book is empty."
    fi
}

# Function to insert a new record with phone number validation
insert_record() {
    echo -n "Enter Name: "
    read name
    
    # Validate phone number
    while true; do
        echo -n "Enter 10-digit Phone Number: "
        read phone
        if [[ $phone =~ ^[0-9]{10}$ ]]; then
            break
        else
            echo "Invalid phone number. Please enter a 10-digit number."
        fi
    done
    
    echo -n "Enter Email: "
    read email
    echo "$name, $phone, $email" >> "$ADDRESS_BOOK"
    echo "Record inserted."
}

# Function to delete a record
delete_record() {
    echo -n "Enter the name of the record to delete: "
    read name
    if grep -q "^$name," "$ADDRESS_BOOK"; then
        grep -v "^$name," "$ADDRESS_BOOK" > temp.txt 
        mv temp.txt "$ADDRESS_BOOK"
        echo "Record deleted."
    else
        echo "Record not found."
    fi
}


# Function to modify a record
modify_record() {
    echo -n "Enter the name of the record to modify: "
    read name
    if grep -q "^$name," "$ADDRESS_BOOK"; then
        grep -v "^$name," "$ADDRESS_BOOK" > temp.txt
        echo -n "Enter new Name: "
        read new_name
        
        # Validate new phone number
        while true; do
            echo -n "Enter new 10-digit Phone Number: "
            read new_phone
            if [[ $new_phone =~ ^[0-9]{10}$ ]]; then
                break
            else
                echo "Invalid phone number. Please enter a 10-digit number."
            fi
        done
        
        echo -n "Enter new Email: "
        read new_email
        echo "$new_name, $new_phone, $new_email" >> temp.txt
        mv temp.txt "$ADDRESS_BOOK"
        echo "Record modified."
    else
        echo "Record not found."
    fi
}

# Main menu loop
while true; do
    echo "---- Address Book Menu ----"
    echo "a) Create Address Book"
    echo "b) View Address Book"
    echo "c) Insert a Record"
    echo "d) Delete a Record"
    echo "e) Modify a Record"
    echo "f) Exit"
    echo -n "Choose an option: "
    read choice

    case $choice in
        a) create_addressbook ;;
        b) view_addressbook ;;
        c) insert_record ;;
        d) delete_record ;;
        e) modify_record ;;
        f) echo "Exiting..."; exit 0 ;;
        *) echo "Invalid option, please try again." ;;
    esac
done
