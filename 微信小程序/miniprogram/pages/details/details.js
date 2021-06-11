// miniprogram/pages/details/details.js
Page({

  /**
   * 页面的初始数据
   */
  data: {
    picurl:"",
    title:"",
    content:"",
    time:"",
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad: function (options) {
    this.getData(options)
    console.log(options)
    //console.log(options.url)
  },
  // 获取数据
  getData({url, id,ctime}) {
    wx.showLoading({
      title: '加载中...',
    })
    let that=this;
     this.setData({
      time:ctime,
     })
    //time=ctime;
    console.log(ctime)
    wx.request({
      url: 'http://api.tianapi.com/txapi/htmltext/index?key=77340d0907ccafc880501201dd9da678&url='+url,
      success: (res) => {
        console.log(res)
        let pic=that.data.picurl.concat(res.data.newslist[0].picture)
        let tit=that.data.title.concat(res.data.newslist[0].title)
        let cntnt=that.data.content.concat(res.data.newslist[0].content)
        var regex = /(<([^>]+)>)/ig
        var body = cntnt
        let result = body.replace(regex, "");
        this.setData({
          picurl:pic,
          title:tit,
          content:result,
        })
        wx.hideLoading();
        
      }
    })
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

  }
})