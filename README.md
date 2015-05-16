# MyDropbox
########################################################################################
Made by :   Harman Kumar  Kabir Chhabra   Haroun Habeeb    
########################################################################################

########################################################################################
Introduction :
########################################################################################

	The purpose of this assignment is to create an application namely "MyDropbox" which enables users on a Network to 
	Upload, Download files and folders on and from a server respectively. The application also has the feature of file and
	folder sharing.

	For guidelines to compile the project, refer to compilation and execution modes section.
	

########################################################################################
Requirements :
########################################################################################


	The libraries required for compilation of the project are : 
		1. Boost for managing directories.
		2. OpenSSL for Security.
		3. QSQLite for maintaining the databases.
		4. Standard C++11 libraries.

	The version of g++ required to compile the project is the c++11 version.

########################################################################################
Compilation and Execution Modes:
########################################################################################

	Compiling the Documentation :

		"make documentation" in the Assignment's folder to compile the .tex file and give a .pdf file corresponding to the documentation.

		"make changes" in the Assignment's folder to compile the .tex file and give a .pdf file corresponding to the changes made.

	Compiling the Project :

		The compilation modes and associated syntax are:

		"make" :							Compiles the source code.

		"make DEBUG" : 						Launches the program in debug mode. Since the application is being made using Qt creator,
											We are using the debug mode provided by Qt.

		"make clean" :  			   		Removes all the .o (object) and .out (executable) files. 

		"make server" : 			   		Launches the server on the machine.

		"make client server=x" : 			Launches a client that gets bound to the server whose
										    IP address and Port number are specified by x.

########################################################################################
User Interface :
########################################################################################

	Functionalities of the User Interface:
	
		The user is provided with four windows to perform the following operations on the .
			
			Window 1: Enter the IP address of the server of MyDropbox application.

			Window 2: Register to MyDropbox.

			Window 3: Login on the application.

			Window 4: Once the user is logged onto the application, he can do the following:

				 1. Upload files and folders on the server.

				 2. Download files and folders from the server.

				 3. Search for other users on the network.

				 4. Share and unshare files and folders with other users on the network.

				 5. Revert a file or folder to a previous version.

				 6. Synchronize the files on the server side and client side.

				 7. Delete files or folders from the Client/Server side.
		


########################################################################################
Bibliography :
########################################################################################

		1) Boost Documentation. 
		2) TCP and Socket Programming : http://www.linuxhowtos.org/C_C++/socket.htm
		3) Secure Connection and OpenSSL : http://simplestcodings.blogspot.in/2010/08/secure-server-client-using-openssl-in-c.html
		4) UI : QT tutorial videos on youtube.

########################################################################################

