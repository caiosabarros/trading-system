#include "thread_utils.h"
#include "lf_queue.h"

struct MyStruct {
	int d_[3];
};

using namespace Common;

auto consumeFunction(LFQueue<MyStruct>* lfq) {
  using namespace std::literals::chrono_literals;
  // as the fns run concurrently, this will allow the main fn to 
  // start with the first logs
  std::this_thread::sleep_for(5s);

  // They run concurrently to decouple the speed of data arrival from the speed of data processing.

  // while lock-free queue is not empty, do this
  while(lfq->size()) {
    // since the lfq is being filled with MyStruct instances
    // get an instance
    const auto d = lfq->getNextToRead();
    // this marks an object as consumed and decreases size()
    lfq->updateReadIndex();

    // logs consumed elements
    std::cout << "consumeFunction read elem:" << d->d_[0] << "," << d->d_[1] << "," << d->d_[2] << " lfq-size:" << lfq->size() << std::endl;

    // sleeps
    std::this_thread::sleep_for(1s);
  }
}
// args just for convention
int main(int, char **) {
  // start with 20
  LFQueue<MyStruct> lfq(20);

  // returns a thread object, not a result
  // this is a ptr to a thread that's being executed now, concurrently
  auto ct = createAndStartThread(-1, "", consumeFunction, &lfq);

  // while the ct is being executed, the main thread also executes
  for(auto i = 0; i < 50; ++i) {
    const MyStruct d{i, i * 10, i * 100};
    *(lfq.getNextToWriteTo()) = d;
    lfq.updateWriteIndex();

    std::cout << "main constructed elem:" << d.d_[0] << "," << d.d_[1] << "," << d.d_[2] << " lfq-size:" << lfq.size() << std::endl;

    using namespace std::literals::chrono_literals;
    std::this_thread::sleep_for(1s);
  }

  ct->join(); // ask for main thread to wait for ct to end its execution

  std::cout << "main exiting." << std::endl;

  return 0; 
}
