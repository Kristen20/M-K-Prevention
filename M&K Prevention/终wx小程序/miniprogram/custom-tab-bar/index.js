Component({
  data: {
    selected: 0,
    "color": "#7A7E83",
    "selectedColor": "#1296db",
    list: [  {
      "iconPath": "/image/homepage.png",   
      "selectedIconPath": "/image/homepage(1).png",
      "pagePath": "pages/index/index",
      "text": "首页"
    },
    {
      "iconPath": "/image/play.png",
      "selectedIconPath": "/image/play(1).png",
      "pagePath": "pages/monitor/monitor",
      "text": "开始监测"
    },
    {
      "iconPath": "/image/info.png",
      "selectedIconPath": "/image/info(1).png",
      "pagePath": "pages/information/information",
      "text": "科学资讯"
    },
    {
      "iconPath": "/image/me.png",
      "selectedIconPath": "/image/me(1).png",
      "pagePath": "pages/MyCenter/MyCenter",
      "text": "个人中心"
    } ]
  },
  attached() {
  },
  methods: {
    switchTab(e) {
      const data = e.currentTarget.dataset
      const url = data.path
      wx.switchTab({url})
      this.setData({
        selected: data.index
      })
    }
  }
})