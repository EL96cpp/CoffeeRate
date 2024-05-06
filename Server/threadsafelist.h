#ifndef THREADSAFELIST_H
#define THREADSAFELIST_H

#include <QList>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <algorithm>

class Connection;
class Message;

template<typename T>
concept HaveGetNicknameMethod = requires (T item) { item.GetNickname(); };


template<typename T>
class ThreadSafeList {

public:
    ThreadSafeList() {}

    ThreadSafeList(const ThreadSafeList& other) = delete;

    std::shared_ptr<T> pop_back() {

        std::lock_guard lock(blocking_mutex);

        auto& item = list.last();
        list.removeLast();
        return item;

    }

    void push_front(std::shared_ptr<T>& item) {

        std::lock_guard lock(blocking_mutex);

        list.push_front(item);

        std::unique_lock unique_lock(cv_mutex);
        condition_variable.notify_one();

    }

    void push_front(std::shared_ptr<T>&& item) {

        std::lock_guard lock(blocking_mutex);

        list.push_front(std::move(item));

        std::unique_lock unique_lock(cv_mutex);
        condition_variable.notify_one();

    }

    bool empty() {

        std::lock_guard lock(blocking_mutex);

        return list.empty();

    }

    void wait() {

        while (empty()) {

            std::unique_lock unique_lock(cv_mutex);
            condition_variable.wait(unique_lock);

        }

    }

    bool contains_user(const QString& nickname) requires ( HaveGetNicknameMethod<T> ) {

        std::lock_guard lock(blocking_mutex);

        auto iterator = std::find_if(list.begin(), list.end(), [&nickname](std::shared_ptr<T>& connection) {
            return connection->GetNickname() == nickname;
        });

        return iterator == list.end();

    }


private:
    QList<std::shared_ptr<T>> list;
    std::mutex blocking_mutex;
    std::mutex cv_mutex;
    std::condition_variable condition_variable;

};



#endif // THREADSAFELIST_H
