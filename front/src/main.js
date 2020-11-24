import Vue from 'vue'

import axios from 'axios'
import VueAxios from 'vue-axios'

import App from './App.vue'
import store from './store/store'
import router from './router'

Vue.config.productionTip = false

Vue.use(VueAxios, axios)

new Vue({
	router,
	store,
	render: h => h(App),
}).$mount('#app')
