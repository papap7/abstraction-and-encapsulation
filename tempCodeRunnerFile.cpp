        for(;;) {
            cout << "Input a 3-digit ID ( 000 | ABC ): ";
            getline(cin, id);
            if (id.length() != 3) {
                cout << "Invalid ID. Please input a 3-digit ID." << endl;
                continue;
            }
            if (isdigit(id[0]) || isdigit(id[1]) || isdigit(id[2])) {
                break;
            }
            if (isupper(id[0]) || isupper(id[1]) || isupper(id[2])) {
                break;
            }
            cout << "Invalid ID. Please input either a 3-digit number (000) or a 3-letter uppercase ID (ABC)." << endl;
        }
        setId(id);