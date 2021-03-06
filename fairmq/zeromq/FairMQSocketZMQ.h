/********************************************************************************
 * Copyright (C) 2014-2018 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRMQSOCKETZMQ_H_
#define FAIRMQSOCKETZMQ_H_

#include <atomic>

#include <memory> // unique_ptr

#include "FairMQSocket.h"
#include "FairMQMessage.h"

class FairMQSocketZMQ : public FairMQSocket
{
  public:
    FairMQSocketZMQ(const std::string& type, const std::string& name, const std::string& id = "", void* context = nullptr);
    FairMQSocketZMQ(const FairMQSocketZMQ&) = delete;
    FairMQSocketZMQ operator=(const FairMQSocketZMQ&) = delete;

    std::string GetId() override;

    bool Bind(const std::string& address) override;
    void Connect(const std::string& address) override;

    int Send(FairMQMessagePtr& msg, const int timeout = 0) override;
    int Receive(FairMQMessagePtr& msg, const int timeout = 0) override;
    int64_t Send(std::vector<std::unique_ptr<FairMQMessage>>& msgVec, const int timeout = 0) override;
    int64_t Receive(std::vector<std::unique_ptr<FairMQMessage>>& msgVec, const int timeout = 0) override;

    int TrySend(FairMQMessagePtr& msg) override;
    int TryReceive(FairMQMessagePtr& msg) override;
    int64_t TrySend(std::vector<std::unique_ptr<FairMQMessage>>& msgVec) override;
    int64_t TryReceive(std::vector<std::unique_ptr<FairMQMessage>>& msgVec) override;

    void* GetSocket() const override;
    int GetSocket(int nothing) const override;

    void Close() override;

    static void Interrupt();
    static void Resume();

    void SetOption(const std::string& option, const void* value, size_t valueSize) override;
    void GetOption(const std::string& option, void* value, size_t* valueSize) override;

    unsigned long GetBytesTx() const override;
    unsigned long GetBytesRx() const override;
    unsigned long GetMessagesTx() const override;
    unsigned long GetMessagesRx() const override;

    bool SetSendTimeout(const int timeout, const std::string& address, const std::string& method) override;
    int GetSendTimeout() const override;
    bool SetReceiveTimeout(const int timeout, const std::string& address, const std::string& method) override;
    int GetReceiveTimeout() const override;

    static int GetConstant(const std::string& constant);

    ~FairMQSocketZMQ() override;

  private:
    void* fSocket;
    std::string fId;
    std::atomic<unsigned long> fBytesTx;
    std::atomic<unsigned long> fBytesRx;
    std::atomic<unsigned long> fMessagesTx;
    std::atomic<unsigned long> fMessagesRx;

    static std::atomic<bool> fInterrupted;

    int fSndTimeout;
    int fRcvTimeout;

    int SendImpl(FairMQMessagePtr& msg, const int flags, const int timeout);
    int ReceiveImpl(FairMQMessagePtr& msg, const int flags, const int timeout);

    int64_t SendImpl(std::vector<std::unique_ptr<FairMQMessage>>& msgVec, const int flags, const int timeout);
    int64_t ReceiveImpl(std::vector<std::unique_ptr<FairMQMessage>>& msgVec, const int flags, const int timeout);
};

#endif /* FAIRMQSOCKETZMQ_H_ */
