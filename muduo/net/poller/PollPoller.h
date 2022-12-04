// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef MUDUO_NET_POLLER_POLLPOLLER_H
#define MUDUO_NET_POLLER_POLLPOLLER_H

#include "muduo/net/Poller.h"

#include <vector>

struct pollfd;

namespace muduo
{
namespace net
{

///
/// IO Multiplexing with poll(2).
///
// 一个 EventLoop 关联一个 Poller, Channel 的 update() 会调用 EventLoop 的 update() 函数，
// EventLoop 的 update() 函数又会调用 Poller 的 poll() 函数.
// Channel 是 fd 的代表，所有操作通过 Channel, 而 Poller 需要监听和返回这些 fd 上注册和实际发生的
// 事件，所以必须提供操作 Channel 的数据结构。
class PollPoller : public Poller
{
 public:

  PollPoller(EventLoop* loop);
  ~PollPoller() override;

  Timestamp poll(int timeoutMs, ChannelList* activeChannels) override;
  void updateChannel(Channel* channel) override;
  void removeChannel(Channel* channel) override;

 private:
  void fillActiveChannels(int numEvents,
                          ChannelList* activeChannels) const;

  typedef std::vector<struct pollfd> PollFdList;
  // ::poll() 函数需要 struct pollfd 的数组地址，所以该结构用于 ::poll 函数参数
  PollFdList pollfds_;
};

}  // namespace net
}  // namespace muduo
#endif  // MUDUO_NET_POLLER_POLLPOLLER_H
