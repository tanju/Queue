/******************************************************************************
 *
 * CircularBuf.h
 *
 * A type independent circular buffer
 *
 * Jan Arnhold, February 2014
 * https://github.com/tanju/Queue
 *
 *****************************************************************************/
 
#ifndef __QUEUE_H
#define __QUEUE_H

// Uncomment to enable semaphore while writing
// Note that although writing is beeing locked this library is not thread save
//#define __QUEUE_SEM


/**
 * Template class Queue
 *
 * Allows to create a circular buffer of any kind of types or objects.
 *
 * E.g. to create a communication queue as follows
 *
 * Queue commQueue<byte, 20>;
 *
 * void loop(){
 *   commQueue.write( Serial.read() );
 *
 *   (...)
 *
 *   while( commQueue.available() ){
 *     Serial.print( commQueue.read() );
 *   }
 * }
 */
template <class T, unsigned int Size>
class Queue 
{
    public:
        /**
         * Creates a new queue
         */
        Queue():
            _pTail( &_Buffer[Size] ),
            _pWrite( _Buffer ),
            _pRead( _Buffer ),
            _dataSize( 0 )
#ifdef __QUEUE_SEM
            , _sem( 0 )
#endif
        {
        }
        
        
        /**
         * Adds an element to the queue unless the queue is full
         */
        unsigned char push( T data ){
            if( _dataSize < Size ){
        #ifdef __QUEUE_SEM
                lock();
        #endif
                *_pWrite = data;
                _pWrite = next( _pWrite );
                _dataSize++;
                
        #ifdef __QUEUE_SEM
                release();
        #endif
                return 1;
            }            
            return 0;
        }

        
        /**
         * Retrieves an element from the queue or 0 if the queue is empty
         */
        T pop(){
            T data = 0; 
            if( _dataSize > 0 ){
                data = *_pRead;
                _pRead = next( _pRead );
                _dataSize--;
            }
            return data;
        }


        /**
         * Adds an emlement. This method is for conveniece for arduino users
         *
         * @see push
         */
        unsigned char write( T data ){
            push( data );
        }
        

        /**
         * Retrieves an emlement. This method is for conveniece for arduino 
         * users
         *
         * @see pop()
         */
        T read(){
            return pop();
        }
        
        
        /**
         * Returns the number of available elements in the queue
         */
        inline int available() const{
            return _dataSize;
        }

        
    private:
        T _Buffer[Size];
        T *_pTail,
             *_pWrite,
             *_pRead;
        unsigned int  _dataSize;

#ifdef __QUEUE_SEM
        unsigned char _sem;
        inline void lock()
        {
            while( _sem );
            _sem = 1;
        }
        

        inline void release()
        {
            _sem = 0;
        }
#endif

        /**
         * returns a pointer to the next element
         * if the end was reached, then this first element of the buffer
         * is returned
         */
        T *next( T *p )
        {
            return ( ++p == _pTail ? _Buffer : p  );
        }

        
     
};
#endif 
