#include "gas_camara_libary.h"
void * stage_thread(void * arg)
{
    main_satge(arg);
}
void* GAS_API_init(){
    handler* handle=(handler*)malloc(sizeof(handler));
    if(handle==NULL){
        printf("error mallocing\n");
        exit(0);
    }
    handle->status=INIT;
    handle->snapshot_bit=false;

    int j=0,i=0;
    char z=(char)255,x=0;
    while(j!=MAX_TEMP*3)
    {
        //rand numbers
        handle->static_mat_rgb[j++]=x;
        handle->static_mat_rgb[j++]=x;
        handle->static_mat_rgb[j++]=z;
    }
    for ( i=0;i<80;i++) {
        handle->static_mat_rgb[i++]=x;
        handle->static_mat_rgb[i++]=x;
        handle->static_mat_rgb[i]=z;
        z-=20;
    }
//    handle->static_mat_rgb[9]=x;
//    handle->static_mat_rgb[10]=x;
//    handle->static_mat_rgb[11]=z;
//    handle->static_mat_rgb[81]=x;
//    handle->static_mat_rgb[82]=x;
//    handle->static_mat_rgb[83]=z;
    rgb_converter_t  *rgb_c_t=init_rgb_converter_t(&(handle->status),handle->static_mat_rgb,SNAPSHOT_ACTIVE,RECORD_ACTIVE);
    capture_t *cap_t=init_capture_t(&(handle->status),RECORD_ACTIVE,STOP_ACTIVE,SNAPSHOT_ACTIVE,&(handle->snapshot_bit));
    yuv_converter_t *yuv_c_t=init_yuv_converter_t(&(handle->status));
    encode_t * enc_t=NULL;
    write_t *wr_t=NULL;
    Queue *q1=createQueue(CAPACITY);
    Queue *q2=createQueue(CAPACITY);
    Queue *q3=createQueue(CAPACITY);
    Queue *q4=createQueue(CAPACITY);
    stage * stage5=init_stage(write_record,NULL,q4,NULL,wr_t);
    stage * stage4=init_stage(encode_record,q4,q3,stage5,enc_t);
    stage * stage3=init_stage(yuv_converter,NULL,q2,stage4,yuv_c_t);
    stage * stage2=init_stage(rgb_converter,q2,q1,stage3,rgb_c_t);
    stage * stage1=init_stage(capture,q1,NULL,stage2,cap_t);
    handle->stages=stage1;
    stage * temp=handle->stages;
    return (void*)handle;
}

void GAS_API_free_all(void* handle){
    handler* my_handler=(handler*)(handle);

    while(my_handler->stages)
    {
        stage * temp= my_handler->stages->next_satge;
        free(my_handler->stages);
        my_handler->stages=temp;
    }
}
int GAS_API_start_record(void* handle){
    printf ("====start_record!====\n");
    handler* my_handler=(handler*)(handle);
    stage * temp= my_handler->stages;
    my_handler->status|=RECORD_ACTIVE;

    while(temp){
        printf("%d",temp->isActive);
        pthread_create(&(temp->thread),NULL,main_satge,temp);
        temp=temp->next_satge;
    }
    return 0;

}
int GAS_API_stop_record(void* handle){

    printf ("====stop_record====\n\r");
    handler* my_handler=(handler*)(handle);
    my_handler->status=my_handler->status&(~RECORD_ACTIVE);
    //we need it to the status controller in the app!
   my_handler->status|=STOP_ACTIVE;
    stage * temp= my_handler->stages;
    for(int i=0;i<5;i++){
        pthread_join(temp->thread,NULL);
        temp=temp->next_satge;
    }
    my_handler->status=my_handler->status&(~STOP_ACTIVE);
    printf("record stopped!!!!!");

    return 0;
}
int GAS_API_start_streaming(streaming_t* stream,char * file_name){
    printf("GAZ_API_start_streaming\n");
    return 1;
}
int GAS_API_stop_streamig(streaming_t*stream){
    printf("GAZ_API_stop_streamig");
    return 1;
}
int GAS_API_do_snapshot(void* handle){
    printf("GAZ_API_do snapshot");
    handler* my_handler=(handler*)(handle);
    my_handler->status|=SNAPSHOT_ACTIVE;
    my_handler->snapshot_bit=true;
    if((my_handler->status & RECORD_ACTIVE))
    {
        return 1;
    }
    stage * temp= my_handler->stages;
    for(int i=0;i<2;i++)
    {
        pthread_create(&temp->thread,NULL,main_satge,temp);
        temp=temp->next_satge;
    }

    temp= my_handler->stages;
    for(int i=0;i<2;i++){
        pthread_join(temp->thread,NULL);
        temp=temp->next_satge;
    }
    //    my_handler->status=SNAPSHOT_ACTIVE&(~my_handler->status);
    //    return 1;
}
char* GAS_API_get_dll_version(){
    printf("GAZ_API_get_dll_version");
    return NULL;
}
char* GAS_API_get_video_statics(record_t* r){
    printf("GAZ_API_get_video_statics");
    return NULL;
}
status GAS_API_get_status(handler * handle){
    printf("GAZ_API_get_status");
    return handle->status;

}
int GAS_API_signal_handler_interrupt(handler * handle){
    printf("GAZ_API_sig_handler");
    if(handle->status&RECORD_ACTIVE)
    {
        GAS_API_stop_record(handle);
    }
}
gazapi_t p_gaz_api= {
    .init=GAS_API_init,
    .free_all=GAS_API_free_all,
    .get_status=GAS_API_get_status,
    .signal_handler_interrupt=GAS_API_signal_handler_interrupt,
    .start_record=GAS_API_start_record,
    .stop_record=GAS_API_stop_record,
    .start_streaming=GAS_API_start_streaming,
    .stop_streamig=GAS_API_stop_streamig,
    .do_snapshot=GAS_API_do_snapshot,
    .get_dll_version=GAS_API_get_dll_version,
    .get_video_statics=GAS_API_get_video_statics,
    .get_status=GAS_API_get_status
};

