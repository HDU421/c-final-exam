set(LIBHOTEL_SOURCE bool.h room.c room.h customer.c customer.h datetime.c datetime.h)
add_library(hotel ${LIBHOTEL_SOURCE})

set(LIBIO_SOURCE bool.h io.c io.h)
add_library(io ${LIBIO_SOURCE})

set(LIBERROR_SOURCE bool.h error.h error.c)
add_library(error ${LIBERROR_SOURCE})
