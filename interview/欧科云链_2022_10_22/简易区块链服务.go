package main

import (
	"fmt"
	"sync"
	"time"
)

type TxA struct {
	TxType string
	Diff   int
}

type TxB struct {
	TxType string
	Diff   []byte
}

type Txs struct {
	txA []*TxA
	txB []*TxB
}

type Block struct {
	index int
	txs   *Txs
}

func MakeTxA() *TxA {
	return &TxA{TxType: "A", Diff: 1}
}
func MakeTxB() *TxB {
	return &TxB{TxType: "B", Diff: []byte("B")}
}

type Service struct {
	txs_cache *Txs
	index     int
	mutex     sync.Mutex
	blockVec  []*Block
}

func NewService() *Service {
	return &Service{
		txs_cache: &Txs{txA: make([]*TxA, 0), txB: make([]*TxB, 0)},
		index:     0,
		blockVec:  make([]*Block, 0),
	}
}
func (s *Service) SendTxsRoutine() {
	for {
		s.mutex.Lock()
		s.txs_cache.txA = append(s.txs_cache.txA, MakeTxA())
		s.txs_cache.txB = append(s.txs_cache.txB, MakeTxB())
		s.mutex.Unlock()
	}
}
func (s *Service) MakeBlock(index int) *Block {
	return &Block{index: index, txs: s.txs_cache}
}
func (s *Service) MakeBlockRoutine() []*Block {
	for {
		time.Sleep(3 * time.Second)
		s.mutex.Lock()
		s.index++
		s.txs_cache = &Txs{txA: make([]*TxA, 0), txB: make([]*TxB, 0)}
		s.blockVec = append(s.blockVec, s.MakeBlock(s.index))
		s.mutex.Unlock()
		fmt.Printf("index:%d", s.index)
	}
	return s.blockVec
}
func (s *Service) CommitBlock(index int) {

}
func main() {
	s := NewService()
	go s.SendTxsRoutine()
	go s.MakeBlockRoutine()
}
