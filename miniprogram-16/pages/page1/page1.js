Page({
  data:{
StartX:'146',
StartY:'365',
leftLooks: '',
topLooks: '',
//半径
radius: '60',
temp:'',
  },

  send1:function(){
    wx.request({
            url: `http://api.heclouds.com/devices/652209764/datapoints`,//设备ID
            header: {
              'api-key': `CXtHFQSRa0fPZ2Vsf87bylgTKOg=`//APIkey
            },
            method: 'POST',
            data: 
            {
              "datastreams":[
                {
                  "id":"CWH",//数据流名称
                  "datapoints":[
                  {
                    "value":"=1"//数据点
                  }
                ]
      
                }
              ]
            },
            success(res){
              console.log(res.data)
            },
            fail(res){
              console.log(res)
            }
          })
      this.setData({
        temp:1
      })
    },
  send2:function(){
    wx.request({
             url: `http://api.heclouds.com/devices/652209764/datapoints`,//设备ID
             header: {
               'api-key': `CXtHFQSRa0fPZ2Vsf87bylgTKOg=`//APIkey
             },
             method: 'POST',
             data: 
             {
               "datastreams":[
                 {
                  "id":"CWH",//数据流名称
                   "datapoints":[
                 {
                    "value":"=2"//数据点
                   }
                 ]
        
                 }
               ]
             },
             success(res){
              console.log(res.data)
            },
            fail(res){
               console.log(res)
            }
          })
      this.setData({
        temp:2
      })
    },
  send3:function(){
        wx.request({
                url: `http://api.heclouds.com/devices/652209764/datapoints`,//设备ID
                header: {
                  'api-key': `CXtHFQSRa0fPZ2Vsf87bylgTKOg=`//APIkey
                },
                method: 'POST',
                data: 
                {
                  "datastreams":[
                    {
                      "id":"CWH",//数据流名称
                      "datapoints":[
                      {
                        "value":"=3"//数据点
                      }
                    ]
          
                    }
                  ]
                },
                success(res){
                  console.log(res.data)
                },
                fail(res){
                  console.log(res)
                }
              })
          this.setData({
            temp:3
          })
        },
  send4:function(){
      wx.request({
                url: `http://api.heclouds.com/devices/652209764/datapoints`,//设备ID
                header: {
                'api-key': `CXtHFQSRa0fPZ2Vsf87bylgTKOg=`//APIkey
              },
              method: 'POST',
              data: 
                  {
                    "datastreams":[
                      {
                        "id":"CWH",//数据流名称
                        "datapoints":[
                        {
                          "value":"=4"//数据点
                        }
                      ]
            
                      }
                    ]
                  },
               success(res){
                 console.log(res.data)
               },
               fail(res){
                console.log(res)
               }
             })
         this.setData({
          temp:4
        })
      },
   send5:function(){
       wx.request({
                    url: `http://api.heclouds.com/devices/652209764/datapoints`,//设备ID
                    header: {
                      'api-key': `CXtHFQSRa0fPZ2Vsf87bylgTKOg=`//APIkey
                    },
                    method: 'POST',
                    data: 
                    {
                      "datastreams":[
                        {
                          "id":"CWH",//数据流名称
                          "datapoints":[
                          {
                            "value":"=5"//数据点
                          }
                        ]
              
                        }
                      ]
                    },
                    success(res){
                      console.log(res.data)
                    },
                    fail(res){
                      console.log(res)
                    }
                  })
              this.setData({
                temp:5
              })
            },
    send6:function(){
        wx.request({
                        url: `http://api.heclouds.com/devices/652209764/datapoints`,//设备ID
                      header: {
                        'api-key': `CXtHFQSRa0fPZ2Vsf87bylgTKOg=`//APIkey
                      },
                     method: 'POST',
                      data: 
                       {
                        "datastreams":[
                          {
                              "id":"CWH",//数据流名称
                           "datapoints":[
                           {
                             "value":"=6"//数据点
                              }
                            ]
                  
                            }
                          ]
                        },
                     success(res){
                     console.log(res.data)
                     },
                      fail(res){
                      console.log(res)
                    }
                   })
              },
  send7:function(){
    wx.request({
      url: `http://api.heclouds.com/devices/652209764/datapoints`,//设备ID
      header: {
      'api-key': `CXtHFQSRa0fPZ2Vsf87bylgTKOg=`//APIkey
              },
      method: 'POST',
            data: 
            {
            "datastreams":[
            {
                "id":"CWH",//数据流名称
                "datapoints":[
                 {
                   "value":"=7"//数据点
                  }
                            ]
                  
                            }
                          ]
                        },
            success(res){
              console.log(res.data)
                        },
            fail(res){
              console.log(res)
                      }
                      })
                },
    sendData:function(a)  {
      if((a>=0&&a<45)||(a>=315&&a<360))
        this.send1();
      else if(a>=45&&a<135) 
        this.send3();
      else if(a>=135&&a<225) 
        this.send2();
      else if(a>=225&&a<315) 
        this.send4();
    },      
    
    
          //获得触碰位置并且进行数据处理获得触碰位置与拖动范围的交点位置
    GetPosition: function (touchX, touchY) {
          var self = this;
          var DValue_X;
          var Dvalue_Y;
          var Dvalue_Z;
          var imageX;
          var imageY;
          var ratio;
          var angle;
          var angleA;
          DValue_X = touchX - self.data.StartX;
          Dvalue_Y = touchY - self.data.StartY;
          Dvalue_Z = Math.sqrt(DValue_X * DValue_X + Dvalue_Y * Dvalue_Y);
          if(DValue_X>=0) 
            angle=(3.14-Math.acos(Dvalue_Y/Dvalue_Z)).toFixed(2);
          else 
            angle=(Math.acos(Dvalue_Y/Dvalue_Z)+3.14).toFixed(2);
          angleA=Math.round(180*angle/3.14);  
          
          //触碰点在范围内
          if (Dvalue_Z <= self.data.radius) {
          imageX = touchX;
          imageY = touchY;
          imageX = Math.round(imageX);
          imageY = Math.round(imageY);
          return { posX: imageX, posY: imageY, Angle:angleA};
          }
           
          //触碰点在范围外
          else {
          ratio = self.data.radius / Dvalue_Z;
          imageX = DValue_X * ratio + 146;
          imageY = Dvalue_Y * ratio + 365;
          imageX = Math.round(imageX);
          imageY = Math.round(imageY);
          return { posX: imageX,posY: imageY,Angle:angleA};
          }
          },
      ImageTouchMove: function (e) {
            var self = this;
            var touchX = e.touches[0].clientX - 40;
            var touchY = e.touches[0].clientY - 40;
            var movePos = self.GetPosition(touchX, touchY);
            self.setData({
              leftLooks: movePos.posX,
              topLooks: movePos.posY,
            });
            
            if(e.timeStamp%5==0)
              self.sendData(movePos.Angle);
            
            
          },
  ImageReturn: function (e) {
  this.send5();
  var self = this;
  self.setData({
  leftLooks: self.data.StartX,
  topLooks: self.data.StartY,
  })
  },
})