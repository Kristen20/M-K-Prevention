//app.js
var subUtils;
var wxcharts;

//计时器初始定义
const defaultTime = {
  defaultWorkTime: 25,
  defaultRestTime: 5
}

App({
  onLaunch: function() { 
    //对抗utils/utils.js is not defined
    subUtils=require('/pages/utils/utils.js');
    wxcharts=require('/pages/utils/wxcharts.js');  

    //计时器时间设定
    let workTime = wx.getStorageSync('workTime')
    let restTime = wx.getStorageSync('restTime')
    if (!workTime) {
      wx.setStorage({
        key: 'workTime',
        data: defaultTime.defaultWorkTime
      })
    }
    if (!restTime) {
      wx.setStorage({
        key: 'restTime',
        data: defaultTime.defaultRestTime
      })
    }

  },
  onShow: function() {
      // Do something when show.
  },
  onHide: function() {
      // Do something when hide.
  },
  globalData: {
    ditance: {}
  }
})