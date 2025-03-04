#configure_file ("Wall.png" ${CMAKE_BINARY_DIR} COPYONLY)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SOUNDS DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/MENU DESTINATION ${CMAKE_BINARY_DIR})

#BACKGROUNDS
configure_file ("bg1.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("long_left.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("long_right.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Menu\\menu_bg.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Menu\\icon.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Menu\\logo.png" ${CMAKE_BINARY_DIR} COPYONLY)

#CHARACTER
configure_file ("harold.bmp" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Kirby.bmp" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("dave.bmp" ${CMAKE_BINARY_DIR} COPYONLY)

#WATCH
configure_file ("stopwatch.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("stopwatch_handle.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("combo_bar.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("combo.png" ${CMAKE_BINARY_DIR} COPYONLY)

#ENEMY
configure_file ("bat.png" ${CMAKE_BINARY_DIR} COPYONLY)

#GIFTS
configure_file ("gift_length.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("gift_gravity.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("gift_attack.png" ${CMAKE_BINARY_DIR} COPYONLY)

#FLOORS
configure_file ("woodboard.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("floors.bmp" ${CMAKE_BINARY_DIR} COPYONLY)

#FONT
configure_file ("font.ttf" ${CMAKE_BINARY_DIR} COPYONLY)

#SOUNDS
configure_file ("Sounds\\bgm.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\harold_bgm.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\jump_lo.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\jump_mid.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\jump_hi.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\hello.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\edge.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\falling.wav" ${CMAKE_BINARY_DIR} COPYONLY)

configure_file ("Sounds\\KBgm.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\KDeath.wav" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\KHello.wav" ${CMAKE_BINARY_DIR} COPYONLY)

configure_file ("Sounds\\Sweet.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\Good.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\Amazing.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\Extreme.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\Fantastic.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\Good.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\Great.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\NoWay.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\Splendid.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\Super.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\Sweet.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\Wow.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\NewHighScore.mp3" ${CMAKE_BINARY_DIR} COPYONLY)

configure_file ("Sounds\\ring.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\HurryUp.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\GameOver.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\TryAgain.mp3" ${CMAKE_BINARY_DIR} COPYONLY)

configure_file ("Sounds\\Alright.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\goinon.ogg" ${CMAKE_BINARY_DIR} COPYONLY)

configure_file ("Sounds\\disco_bgm.mp3" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\ahey.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\cmonyo.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\diggin.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\ho.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\stayinalive.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Sounds\\watchit.ogg" ${CMAKE_BINARY_DIR} COPYONLY)