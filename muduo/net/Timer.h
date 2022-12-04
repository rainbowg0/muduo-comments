// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef MUDUO_NET_TIMER_H
#define MUDUO_NET_TIMER_H

#include "muduo/base/Atomic.h"
#include "muduo/base/Timestamp.h"
#include "muduo/net/Callbacks.h"

namespace muduo
{
namespace net
{

///
/// Internal class for timer event.
///
class Timer : noncopyable
{
 public:
  Timer(TimerCallback cb, Timestamp when, double interval)
    : callback_(std::move(cb)),
      expiration_(when),
      interval_(interval),
      repeat_(interval > 0.0),
      sequence_(s_numCreated_.incrementAndGet())
  { }

  void run() const
  {
    callback_();
  }

  Timestamp expiration() const  { return expiration_; }
  bool repeat() const { return repeat_; }
  int64_t sequence() const { return sequence_; }

  void restart(Timestamp now);

  static int64_t numCreated() { return s_numCreated_.get(); }

 private:
  // 定时执行函数
  const TimerCallback callback_;
  // 超时时间
  Timestamp expiration_;
  // 执行间隔
  const double interval_;
  // 是否重复执行任务
  const bool repeat_;
  // 序列号，每个 Timer 不同。
  const int64_t sequence_;

  // 通过 s_numCreated_ 生成 sequence_, 保证每个 Timer 的 sequence_ 不同。
  static AtomicInt64 s_numCreated_;
};

}  // namespace net
}  // namespace muduo

#endif  // MUDUO_NET_TIMER_H
