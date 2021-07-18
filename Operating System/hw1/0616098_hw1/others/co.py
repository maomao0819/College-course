# import asyncio
# loop = asyncio.get_event_loop() #建立一個Event Loop
# a = False
# async def example1(): # 定義一個中間會被中斷的協程
#     print("Start example1 coroutin.")
#     print("lala")
#     await asyncio.sleep(1) # 中斷協程一秒
#     print("bala")
#     print("Finish example1 coroutin.")

# async def example2(): # 定義一個協程
#     print("Start example2 coroutin.")
#     print("lala")
#     print("bala")
#     # do some process...
#     print("Finish example2 coroutin.")

# tasks = [ # 建立一個任務列表
#     asyncio.ensure_future(example1()),
#     asyncio.ensure_future(example2()),
# ]

# loop.run_until_complete(asyncio.wait(tasks))

import asyncio
import time

now = lambda: time.time()

async def dosomething(num):
    print('第 {} 任務，第一步'.format(num))
    await asyncio.sleep(0.001)
    print('第 {} 任務，第二步'.format(num))
    return '第 {} 任務完成'.format(num)

async def raise_error(num):
    raise ValueError
    print('這邊不會執行到')

async def main():
    tasks = [dosomething(i) for i in range(5)]
    tasks1 = [raise_error(i) for i in range(5)]

    results = await asyncio.gather(*tasks, *tasks1, return_exceptions=True)
    print(results)


if __name__ == '__main__':

    start = now()
    asyncio.run(main())
    print('TIME: ', now() - start)