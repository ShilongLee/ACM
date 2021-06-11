// miniprogram/pages/home/home.js
var appd = getApp();
Page({

  /**
   * 页面的初始数据
   */
  data: {
    background: ['https://cdn.akamai.steamstatic.com/steam/apps/105600/header.jpg?t=1590092560', 'https://cdn.akamai.steamstatic.com/steam/apps/322330/header_alt_assets_1_schinese.jpg?t=1622738587', 'https://cdn.akamai.steamstatic.com/steam/apps/1238810/header.jpg?t=1615895305', 'https://cdn.akamai.steamstatic.com/steam/apps/275850/header_alt_assets_1.jpg?t=1622639949', 'https://cdn.akamai.steamstatic.com/steam/apps/730/header.jpg?t=1612812939'],
    indicatorDots: true,
    vertical: false,
    autoplay: false,
    circular: false,
    interval: 2000,
    duration: 500,
    previousMargin: 0,
    nextMargin: 0,
    List: [],
    page: 1,
  },
  onSwiperTap:function(event) {
    var id= event.target.dataset.id;
    wx.navigateTo({

      url: "../swiper_detail_" + id+"/swiper_detail_"+id
      
      })
  },
  onLoad: function (options) {
    this.getData();
  },
  goDetail(e) {
    console.log(e);
    //appd.globalData.detailurl=e.currentTarget.dataset.url,
    wx.navigateTo({
      url: '../details/details?id=' + e.currentTarget.dataset.id.id + '&url=https:' + e.currentTarget.dataset.id.url + '&ctime=' + e.currentTarget.dataset.id.ctime,
    })
  },
  getData() {
    wx.showLoading({
      title: '加载中...',
    })
    let that = this;
    return new Promise((resolve, reject) => {
      wx.request({
        url: `http://api.tianapi.com/esports/index?key=77340d0907ccafc880501201dd9da678&num=10&page=${this.data.page}`,
        success(res) {
          console.log(res)
          let _newArr = that.data.List.concat(res.data.newslist)
          that.setData({
            List: _newArr,
          })
          wx.hideLoading();
          resolve();
        }
      })
    })
  },
  /**
   * 生命周期函数--监听页面加载
   */
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
    this.setData({
      List: [],
      page: 0
    })
    this.getData().then(() => {
      wx.stopPullDownRefresh()
    }).catch(() => {

    });
  },

  /**
   * 页面上拉触底事件的处理函数
   */
  onReachBottom: function () {
    this.setData({
      page: this.data.page + 1
    })
    this.getData();
  },

  /**
   * 用户点击右上角分享
   */
  onShareAppMessage: function () {

  }
})