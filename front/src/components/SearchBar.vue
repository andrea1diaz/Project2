<template>
	<div id="search-bar">
		<div class="icons">
			<span class="dot"></span>
			<span class="dot" style="margin-left: 0px;"></span>
		</div>
		<div class="search">
			<input
				id="search"
				type="text"
				placeholder="Search..."
				autocomplete="off"
				v-model="inputSearch"
				v-on:keyup.enter="emitToParent"
			/>
		</div>
	</div>
</template>

<script>
	export default {
		name: 'SearchBar',
		methods: {
			emitToParent: function () {
				let to_send = this.inputSearch.replace(/ /g,"_");
				this.$emit('childToParent', to_send)
			},
		}
	}
</script>

<style scoped>
	#search-bar {
		border-bottom: solid black 4px;
		display: flex;
		flex-flow: row;
		justify-content: space-between;
	}

	#search-bar .icons {
		display: block;
	}

	#search-bar .search {
		margin: 20px;
	}

	.dot {
		height: 20px;
		width: 20px;
		border-radius: 50%;
		border: solid black 4px;
		display: inline-block;
		margin: 10px;
	}

	#search {
		width: 200px;
		border: solid black 3px;
		border-radius: 8px;
		padding: 7px 10px;
		background-color: unset;
	}

	#search:focus {
		outline: unset;
	}
</style>
