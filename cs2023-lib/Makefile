CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g -fsanitize=address,undefined

TESTS := test_01 test_02 test_03 test_04 test_05
BINS  := $(addprefix tests/,$(TESTS))

.PHONY: all test clean

all: $(BINS)

tests/%: tests/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

test: all
	@for b in $(BINS); do \
		echo "== $$b =="; \
		./$$b || exit 1; \
	done
	@echo "TODOS LOS TESTS OK"

clean:
	rm -f $(BINS)
