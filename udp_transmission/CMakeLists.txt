cmake_minimum_required(VERSION 2.8)
project( lan_vid_pseudostream )
find_package( OpenCV REQUIRED )

add_executable( server_msg message/Server_msg.cpp lib/PracticalSocket.cpp )
target_link_libraries( server_msg ${OpenCV_LIBS} )
add_executable( client_msg message/Client_msg.cpp lib/PracticalSocket.cpp )
target_link_libraries( client_msg ${OpenCV_LIBS} )

add_executable( server_img image/Server_img.cpp lib/PracticalSocket.cpp )
target_link_libraries( server_img ${OpenCV_LIBS} )
add_executable( client_img image/Client_img.cpp lib/PracticalSocket.cpp )
target_link_libraries( client_img ${OpenCV_LIBS} )

add_executable( server_video video/Server_video.cpp lib/PracticalSocket.cpp )
target_link_libraries( server_video ${OpenCV_LIBS} )
add_executable( client_video video/Client_video.cpp lib/PracticalSocket.cpp )
target_link_libraries( client_video ${OpenCV_LIBS} )

add_executable( server_cmd command/Server_cmd.cpp lib/PracticalSocket.cpp )
target_link_libraries( server_cmd ${OpenCV_LIBS} )
add_executable( client_cmd command/Client_cmd.cpp lib/PracticalSocket.cpp )
target_link_libraries( client_cmd ${OpenCV_LIBS} )
