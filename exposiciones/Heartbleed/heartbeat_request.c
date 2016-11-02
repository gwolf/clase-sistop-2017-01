
//  IMPLEMENTACIÓN DEL MENSAJE HEARTBEAT_REQUEST
int
dtls1_heartbeat(SSL *s)
       {
       unsigned char *buf, *p;
       int ret;
       unsigned int payload = 18; /* Sequence number + random bytes */
       unsigned int padding = 16; /* Use minimum padding */
       /* Only send if peer supports and accepts HB requests... */
       if (!(s->tlsext_heartbeat & SSL_TLSEXT_HB_ENABLED) ||
           s->tlsext_heartbeat & SSL_TLSEXT_HB_DONT_SEND_REQUESTS)
               {
               SSLerr(SSL_F_DTLS1_HEARTBEAT,SSL_R_TLS_HEARTBEAT_PEER_DOESNT_ACCEPT);
               return -1;
               }
       /* ...and there is none in flight yet... */
       if (s->tlsext_hb_pending)
               {
               SSLerr(SSL_F_DTLS1_HEARTBEAT,SSL_R_TLS_HEARTBEAT_PENDING);
               return -1;
               }
       /* ...and no handshake in progress. */
       if (SSL_in_init(s) || s->in_handshake)
               {
               SSLerr(SSL_F_DTLS1_HEARTBEAT,SSL_R_UNEXPECTED_MESSAGE);
               return -1;
               }
       /* Check if padding is too long, payload and padding
        * must not exceed 2^14 - 3 = 16381 bytes in total.
        */
       OPENSSL_assert(payload + padding <= 16381);
       /* Create HeartBeat message, we just use a sequence number
        * as payload to distuingish different messages and add
        * some random stuff.
        *  - Message Type, 1 byte
        *  - Payload Length, 2 bytes (unsigned int)
        *  - Payload, the sequence number (2 bytes uint)
        *  - Payload, random bytes (16 bytes uint)
        *  - Padding
        */
       buf = OPENSSL_malloc(1 + 2 + payload + padding);
       p = buf;
       /* Message Type */
       *p++ = TLS1_HB_REQUEST;
       /* Payload length (18 bytes here) */
       s2n(payload, p);
       /* Sequence number */
       s2n(s->tlsext_hb_seq, p);
       /* 16 random bytes */
       RAND_pseudo_bytes(p, 16);
       p += 16;
       /* Random padding */
       RAND_pseudo_bytes(p, padding);
       ret = dtls1_write_bytes(s, TLS1_RT_HEARTBEAT, buf, 3 + payload + padding);
       if (ret >= 0)
               {
               if (s->msg_callback)
                      s->msg_callback(1, s->version, TLS1_RT_HEARTBEAT,
                              buf, 3 + payload + padding,
                              s, s->msg_callback_arg);
               dtls1_start_timer(s);
               s->tlsext_hb_pending = 1;
               }
       OPENSSL_free(buf);
return ret; 
}