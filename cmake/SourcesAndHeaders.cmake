set(sources
    src/book.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    include/bookshop/book.hpp
    include/bookshop/shop.hpp
    include/bookshop/cart.hpp
)

set(test_sources
  src/bookTests.cpp
  src/cartTests.cpp
  src/shopTests.cpp
)
