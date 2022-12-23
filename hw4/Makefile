X = 5
N = 10

main: 
	@make main1

main1: main1.c
	@gcc main1.c -lpthread -o main1

main2: main2.c
	@gcc main2.c -lpthread -o main2
	@./main2 $(X) $(N)

.PHONY: clean
clean:
	@rm -f main main1 main2