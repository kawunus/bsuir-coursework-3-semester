//defined snippets: |snippet_1
//begin:snippet_1
#include <iostream>
#include <limits>
#include <sqlite3.h>
#include <utility>
#include <vector>

#include "model/Admin.h"
#include "model/Database.h"
#include "model/Entity.h"
#include "model/System.h"
#include "model/User.h"


int main() {
    System system;

    switch (system.login()) {
        case 1: {
            Admin admin;
            admin.start();
            break;
        }

        case 2: {
            //User user;
           // user.start();
            break;
        }

        case 0: {
            return 0;
        }
    }
}

//end:snippet_1
