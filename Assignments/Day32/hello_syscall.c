SYSCALL_DEFINE3(reverse_string, const char __user *, user_input, char __user *, user_output, size_t, len)
{
    char kbuf[256];
    int i;
    
    if(len == 0 || len >= sizeof(kbuf))
        return -EINVAL;
    
    /* copy from user -> kernel */
    if(copy_from_user(kbuf, user_input, len))
        return -EFAULT;
        
    kbuf[len] = '\0';
    
    printk(KERN INFO "reverse_string called: input=%s len=%zu\n",kbuf,len);
    
    /* Reversing the string logic */
    
    for(i=0;i<len/2;i++)
    {
        char temp = kbuf[i];
        kbuf[i] = kbuf[len -i -1];
        kbuf[len -i -1] = temp;
    }
    
    /* copy kernel -> user */
    
    if(copy_to_user(user_output, kbuf, len+1))
        return -EFAULT;
        
    return 0;
}