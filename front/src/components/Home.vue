<template>
	<div id="home">
		<SearchBar
			v-on:childToParent="onSearch"
		/>
		<Result
			:results=this.search_results
			:componentKey= this.send
		/>
	</div>
</template>

<script>
	import SearchBar from '@/components/SearchBar'
	import Result from '@/components/Result'
	import { mapState, mapActions } from 'vuex'


	export default {
		name: 'Home',
		components: {
			SearchBar,
			Result
		},
		data: function () {
			return {
				toSend: '',
				send: 0
			}
		},
		computed: {
			...mapState('collection', ['search_results'])
		},
		methods: {
			...mapActions('collection', ['getResults']),
			onSearch: async function (value) {

				this.toSend = value;
				var url = "http://localhost:3000/api/find/" + value
				console.log(url)
				this.$router.push("http://localhost:3000/api/find/" + value)
			}
		}
	}
</script>

<style scoped>
#home {
	font-family: Avenir, Helvetica, Arial, sans-serif;
	-webkit-font-smoothing: antialiased;
	-moz-osx-font-smoothing: grayscale;
	text-align: center;
	border: solid black 4px;
	border-radius: 15px;
	box-shadow: 5px 5px black;
	margin: 30px;
	height: -webkit-fill-available;
	width: -webkit-fill-available;
    position: fixed;
	overflow: hidden;
}


	
</style>
