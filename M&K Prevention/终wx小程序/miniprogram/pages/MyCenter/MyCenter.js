// pages/pra/pra.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {

  },

  /**
   * 生命周期函数--监听页面初次渲染完成
   */
  onReady: function () {

  },

  /**
   * 生命周期函数--监听页面显示
   */
  onShow: function () {

  },

  /**
   * 生命周期函数--监听页面隐藏
   */
  onHide: function () {

  },

  /**
   * 生命周期函数--监听页面卸载
   */
  onUnload: function () {

  },

  /**
   * 页面相关事件处理函数--监听用户下拉动作
   */
  onPullDownRefresh: function () {

  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {

  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  },

  toLogs:function(){
    wx.navigateTo({
      url: '/pages/logs/logs',
    })
  },

  instruc:function( options){
    wx.navigateTo({
      url: '/pages/data/data',
    })
    console.log("点击事件成功")
   
    
  },

  

  //获取onenet上的数据
  get: function () {
    const requestTask = wx.request({
      url: 'http://api.heclouds.com/devices/644262390/datapoints?datastream_id=distance',
      header: {
        'content-type': 'application/json',
        'api-key': 'mVFOQnBlsoTAgKbA0HQVSOm37oo='
      },
      success: function (res) {
        var app = getApp()
        var that = this
      
        app.globalData.distance = res.data.data.datastreams[0]
        var a=app.globalData.distance.datapoints[0].value
        console.log(app.globalData.distance)
      }
    })
    
  },

  //将控制台上的数据打印到屏幕上（fail）
  input1(app){
		this.setData({
			num:app.globalData.distance.datapoints[0].value
    })
    wx.setStorageSync('num',num)
	}
})
 
